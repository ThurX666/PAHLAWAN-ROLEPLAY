#define UpperToLower(%1) for( new ToLowerChar; ToLowerChar < strlen( %1 ); ToLowerChar ++ ) if ( %1[ ToLowerChar ]> 64 && %1[ ToLowerChar ] < 91 ) %1[ ToLowerChar ] += 32
#define PRESSED(%0) \
    (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

#define HOLDING(%0) \
    ((newkeys & (%0)) == (%0))

#define RELEASED(%0) \
    (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

#define PermissionError(%0) ShowTDN(%0, NOTIFICATION_ERROR, "Anda tidak memiliki wewenang untuk perintah tersebut!")
#define SendAdm(%1,%2) SendClientMessageEx(%1, Y_LIGHTRED, "AdmCmd: "%2)
#define SEM(%1,%2) SendClientMessageEx(%1, 0xFF6347AA, "[Error] "%2)
#define SUM(%1,%2) SendClientMessage(%1, 0xFF6347AA, "(Syntax) {AFAFAF}"%2)
#define SIM(%1,%2) SendClientMessageEx(%1, 0x80FF80AA, "[Info] "%2)
#define SyntaxMsg(%1,%2) SendClientMessage(%1, X11_GREY38, "[Syntax] "WHITE""%2)

//cheat
#define MAX_WARNS_AC 3 //Max warns before kick in severe case 1
#define AC_MESSAGE_COLOR -1

#define MAX_CHARS 5
#define MAX_PWARNS 20

#define MAX_FACTIONS 13
#define MAX_FACTIONS_ITEMS 500
#define MAX_COMPANY_ITEMS 500
#define MAX_ADVERTISEMENT 15
#define MAX_JOBGROUPS 1000

#define MAX_PAGINATION_PAGES 10
#define MAX_MEMBER_ROWS 10
#define MAX_MDC_ROWS 10

#define DATABASE_ADDRESS "localhost"
#define DATABASE_USERNAME "root"
#define DATABASE_PASSWORD ""
#define DATABASE_NAME "arivena"

#if !defined BCRYPT_HASH_LENGTH
	#define BCRYPT_HASH_LENGTH 250
#endif

#if !defined BCRYPT_COST
	#define BCRYPT_COST 12
#endif

//sound id
#define SOUND_CHECKPOINT		(1139)
#define SOUND_GET_ITEM			(40405)
#define SOUND_NOTIF_BOX			(30801)
#define SOUND_LOCK_CAR_DOOR     (24600)
#define SOUND_LOGIN_START       (1185)
#define SOUND_LOGIN_END         (1186)
#define SOUND_DMV_PASS_START    (1187)
#define SOUND_DMV_PASS_END      (1188)
#define SOUND_SLAP              (1190)
#define SOUND_CAR_MOD           (1133)
#define SOUND_FUEL_DECREASE     (1131)
#define SOUND_FIREALARM_START   (3401)
#define SOUND_FIREALARM_END     (3402)
#define MDC_ERROR               (21001)
#define MDC_SELECT              (21000)
#define MDC_OPEN                (45400)

//JUMLAH MAX
#define MAX_ADMIN_VEHICLES 100

#define BAN_MASK \
	(-1<<(32-(26))) // 26 = this is the CIDR ip detection range

#define TEXT_HOSTNAME   "Pahlawan Roleplay | est. 1 November 2020"
#define TEXT_GAMEMODE	"PHRP v1.8.3 - Reborn"
#define TEXT_WEBURL		"bit.ly/pahlawan-rp"
#define TEXT_LANGUAGE	"Bahasa Indonesia"
#define TEXT_IPADDRESS	"127.0.0.1"
#define TEXT_IPPORT		":7777"

//CONVERT COLOR
#define RGB%0(%1,%2,%3) ((((%1) & 0xff) << 16) | (((%2) & 0xff) << 8) | ((%3) & 0xff))
#define RGBA%0(%1,%2,%3,%4) ((RGB(%1,%2,%3) << 8) | ((%4) & 0xff))
#define ARGB%0(%1,%2,%3,%4) ((RGB(%1,%2,%3)) | (((%4) & 0xff) << 24))

#define RGBA2ARGB%0(%1) ((((%1) & 0xffffff00) >>> 8) | (((%1) & 0x000000ff) << 24))
#define RGBA2RGB%0(%1) (((%1) & 0xffffff00) >>> 8)
#define ARGB2RGBA%0(%1) ((((%1) & 0x000000ff) << 8) | (((%1) & 0xff000000) >>> 24))
#define ARGB2RGB%0(%1) (((%1) & 0x00ffffff))

//animasi untuk GYM
// index 52 -> kamera harus berhadapan
// index 577 -> kamera berhadapan
// index 649 (sepeda) -> searah sepeda, sejajar bangku
