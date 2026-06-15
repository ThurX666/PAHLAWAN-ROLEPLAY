<?php
class SampQuery {
    private $serverIP;
    private $port;

    public function __construct($serverIP, $port = 7777) {
        $this->serverIP = gethostbyname($serverIP);
        $this->port = (int)$port;
    }

    private function getPacket($opcode) {
        $packet = "SAMP";
        $ipParts = explode(".", $this->serverIP);
        if (count($ipParts) !== 4) $ipParts = [127,0,0,1];
        foreach ($ipParts as $part) $packet .= chr((int)$part);
        $packet .= chr($this->port & 0xFF) . chr($this->port >> 8 & 0xFF) . $opcode;
        return $packet;
    }

    public function getInfo() {
        $packet = $this->getPacket('i');
        $response = "";

        // Prioritas 1: Socket extension (Sangat direkomendasikan untuk Windows/XAMPP localhost UDP loopback)
        if (function_exists('socket_create')) {
            $sock = @socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
            if ($sock) {
                @socket_set_option($sock, SOL_SOCKET, SO_RCVTIMEO, array("sec"=>2, "usec"=>0));
                @socket_sendto($sock, $packet, strlen($packet), 0, $this->serverIP, $this->port);
                $from = "";
                $port_recv = 0;
                @socket_recvfrom($sock, $response, 2048, 0, $from, $port_recv);
                @socket_close($sock);
            }
        }

        // Prioritas 2: Fallback ke fsockopen (Standard hosting)
        if (empty($response)) {
            $fp = @fsockopen("udp://" . $this->serverIP, $this->port, $errno, $errstr, 2);
            if ($fp) {
                stream_set_timeout($fp, 2);
                fwrite($fp, $packet);
                $response = fread($fp, 2048);
                fclose($fp);
            }
        }

        if(empty($response) || substr($response, 0, 4) !== "SAMP" || $response[10] !== 'i') {
            return false;
        }

        $data = substr($response, 11);
        $offset = 0;
        
        $passworded = ord($data[$offset++]);
        $players = ord($data[$offset++]) | (ord($data[$offset++]) << 8);
        $maxPlayers = ord($data[$offset++]) | (ord($data[$offset++]) << 8);

        $hostnameLen = ord($data[$offset++]) | (ord($data[$offset++]) << 8) | (ord($data[$offset++]) << 16) | (ord($data[$offset++]) << 24);
        $hostname = mb_convert_encoding(substr($data, $offset, $hostnameLen), "UTF-8", "auto");
        $offset += $hostnameLen;

        $gamemodeLen = ord($data[$offset++]) | (ord($data[$offset++]) << 8) | (ord($data[$offset++]) << 16) | (ord($data[$offset++]) << 24);
        $gamemode = mb_convert_encoding(substr($data, $offset, $gamemodeLen), "UTF-8", "auto");
        $offset += $gamemodeLen;

        $mapnameLen = ord($data[$offset++]) | (ord($data[$offset++]) << 8) | (ord($data[$offset++]) << 16) | (ord($data[$offset++]) << 24);
        $mapname = mb_convert_encoding(substr($data, $offset, $mapnameLen), "UTF-8", "auto");

        return [
            'password' => $passworded,
            'players' => $players,
            'max_players' => $maxPlayers,
            'hostname' => $hostname,
            'gamemode' => $gamemode,
            'mapname' => $mapname
        ];
    }

    public function getDetailedPlayers() {
        $packet = $this->getPacket('d');
        $response = "";

        if (function_exists('socket_create')) {
            $sock = @socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
            if ($sock) {
                @socket_set_option($sock, SOL_SOCKET, SO_RCVTIMEO, array("sec"=>2, "usec"=>0));
                @socket_sendto($sock, $packet, strlen($packet), 0, $this->serverIP, $this->port);
                $from = "";
                $port_recv = 0;
                @socket_recvfrom($sock, $response, 2048, 0, $from, $port_recv);
                @socket_close($sock);
            }
        }

        if (empty($response)) {
            $fp = @fsockopen("udp://" . $this->serverIP, $this->port, $errno, $errstr, 2);
            if ($fp) {
                stream_set_timeout($fp, 2);
                fwrite($fp, $packet);
                $response = fread($fp, 2048);
                fclose($fp);
            }
        }

        if(empty($response) || substr($response, 0, 4) !== "SAMP" || $response[10] !== 'd') {
            return false;
        }

        $data = substr($response, 11);
        $offset = 0;
        
        // 2 bytes for player count
        if (strlen($data) < 2) return [];
        $playerCount = ord($data[$offset++]) | (ord($data[$offset++]) << 8);

        $players = [];
        for ($i = 0; $i < $playerCount; $i++) {
            if ($offset >= strlen($data)) break;
            
            // 1 byte for player ID
            $playerID = ord($data[$offset++]);
            
            // 1 byte for name length
            if ($offset >= strlen($data)) break;
            $nameLen = ord($data[$offset++]);
            
            // name length bytes for name
            if ($offset + $nameLen > strlen($data)) break;
            $name = substr($data, $offset, $nameLen);
            $offset += $nameLen;
            
            // 4 bytes for score
            if ($offset + 4 > strlen($data)) break;
            // Handle negative scores properly by unpacking as signed long
            $scoreData = substr($data, $offset, 4);
            $scoreArr = unpack("l", $scoreData);
            $score = $scoreArr[1];
            $offset += 4;
            
            // 4 bytes for ping
            if ($offset + 4 > strlen($data)) break;
            $pingData = substr($data, $offset, 4);
            $pingArr = unpack("l", $pingData);
            $ping = $pingArr[1];
            $offset += 4;
            
            $players[] = [
                'id' => $playerID,
                'name' => mb_convert_encoding($name, "UTF-8", "auto"),
                'score' => $score,
                'ping' => $ping
            ];
        }

        return $players;
    }
}
?>
