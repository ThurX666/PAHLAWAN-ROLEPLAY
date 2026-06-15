#define MAX_CONTACTS 100

new 
    Text:RebootScreenTD[7],
    Text:LockScreenTD[11],
    Text:GreyBoxBackground,
    Text:YellowBoxBackground,
    Text:RedBoxBackground,
    Text:GreenBoxBackground,
    Text:BlueBoxBackground,
    Text:CyanBoxBackground,
    Text:PinkBoxBackground,
    Text:OrangeBoxBackground,
    Text:CocoBoxBackground,
    Text:CreamBoxBackground,
    Text:HomeButtonPhone[2],
    Text:FingerButtonPhone,
    Text:RedButtonIncomingPhone,
    Text:RedButtonOutcomingPhone,
    Text:GreenButtonIncomingPhone,
    Text:BankingTD[11],

    Text:TwitterLoginTD[6],
    Text:TwitterMainTD[5],
    Text:SpotifyTD[14],
    Text:UberPhoneTD[12],

    //menu
    Text:MainMenuTD[14],
    Text:PhoneMainMenuClock,
    Text:KontakButtonPhone,
    Text:GPSButtonPhone,
    Text:AirdropButtonPhone,
    Text:BankingButtonPhone,
    Text:AppStoreButtonPhone,
    Text:SettingsButtonPhone,
    Text:CallButtonPhone,
    Text:WhatsappButtonPhone[3],
    Text:SpotifyButtonPhone[3],
    Text:TwitterButtonPhone[3],
    Text:UberButtonPhone[3],
    Text:YellowButtonPhone[3],

    //appstore
    Text:AppStoreTD[26],
    Text:InstallWAButtonPhone,
    Text:InstallSpotifyButtonPhone,
    Text:InstallTwitterButtonPhone,
    Text:InstallUberButtonPhone,
    Text:InstallYellowButtonPhone,

    //contact
    Text:ContactTD[5],

    //settings
    Text:SettingsTD[3];

new PlayerText:ContactNameTD[MAX_PLAYERS],
    PlayerText:StatusDialingTD[MAX_PLAYERS],
    PlayerText:PlayerBankingTD[MAX_PLAYERS][3],
    PlayerText:PhoneRebootBar[MAX_PLAYERS],
    PlayerText:TwitterInfoTD[MAX_PLAYERS],
    PlayerText:UberMainTD[MAX_PLAYERS][2];

CreatePhoneRebootTD()
{
    RebootScreenTD[0] = TextDrawCreate(574.000000, 208.000000, "_");
	TextDrawFont(RebootScreenTD[0], 0);
	TextDrawLetterSize(RebootScreenTD[0], 0.608331, 22.300006);
	TextDrawTextSize(RebootScreenTD[0], 298.500000, 98.000000);
	TextDrawSetOutline(RebootScreenTD[0], 1);
	TextDrawSetShadow(RebootScreenTD[0], 0);
	TextDrawAlignment(RebootScreenTD[0], 2);
	TextDrawColor(RebootScreenTD[0], 255);
	TextDrawBackgroundColor(RebootScreenTD[0], 255);
	TextDrawBoxColor(RebootScreenTD[0], 505290495);
	TextDrawUseBox(RebootScreenTD[0], 1);
	TextDrawSetProportional(RebootScreenTD[0], 1);
	TextDrawSetSelectable(RebootScreenTD[0], 0);

    RebootScreenTD[1] = TextDrawCreate(563.000000, 290.000000, "ld_beat:chit");
	TextDrawFont(RebootScreenTD[1], 4);
	TextDrawLetterSize(RebootScreenTD[1], 0.600000, 2.000000);
	TextDrawTextSize(RebootScreenTD[1], 19.000000, 25.000000);
	TextDrawSetOutline(RebootScreenTD[1], 1);
	TextDrawSetShadow(RebootScreenTD[1], 0);
	TextDrawAlignment(RebootScreenTD[1], 1);
	TextDrawColor(RebootScreenTD[1], -1);
	TextDrawBackgroundColor(RebootScreenTD[1], 255);
	TextDrawBoxColor(RebootScreenTD[1], 50);
	TextDrawUseBox(RebootScreenTD[1], 1);
	TextDrawSetProportional(RebootScreenTD[1], 1);
	TextDrawSetSelectable(RebootScreenTD[1], 0);

	RebootScreenTD[2] = TextDrawCreate(569.000000, 290.000000, "ld_beat:chit");
	TextDrawFont(RebootScreenTD[2], 4);
	TextDrawLetterSize(RebootScreenTD[2], 0.600000, 2.000000);
	TextDrawTextSize(RebootScreenTD[2], 19.000000, 25.000000);
	TextDrawSetOutline(RebootScreenTD[2], 1);
	TextDrawSetShadow(RebootScreenTD[2], 0);
	TextDrawAlignment(RebootScreenTD[2], 1);
	TextDrawColor(RebootScreenTD[2], -1);
	TextDrawBackgroundColor(RebootScreenTD[2], 255);
	TextDrawBoxColor(RebootScreenTD[2], 50);
	TextDrawUseBox(RebootScreenTD[2], 1);
	TextDrawSetProportional(RebootScreenTD[2], 1);
	TextDrawSetSelectable(RebootScreenTD[2], 0);

	RebootScreenTD[3] = TextDrawCreate(578.000000, 294.000000, "ld_beat:chit");
	TextDrawFont(RebootScreenTD[3], 4);
	TextDrawLetterSize(RebootScreenTD[3], 0.600000, 2.000000);
	TextDrawTextSize(RebootScreenTD[3], 11.500000, 15.000000);
	TextDrawSetOutline(RebootScreenTD[3], 1);
	TextDrawSetShadow(RebootScreenTD[3], 0);
	TextDrawAlignment(RebootScreenTD[3], 1);
	TextDrawColor(RebootScreenTD[3], 505290495);
	TextDrawBackgroundColor(RebootScreenTD[3], 255);
	TextDrawBoxColor(RebootScreenTD[3], 50);
	TextDrawUseBox(RebootScreenTD[3], 1);
	TextDrawSetProportional(RebootScreenTD[3], 1);
	TextDrawSetSelectable(RebootScreenTD[3], 0);

	RebootScreenTD[4] = TextDrawCreate(578.000000, 284.000000, "/");
	TextDrawFont(RebootScreenTD[4], 0);
	TextDrawLetterSize(RebootScreenTD[4], 0.333332, 0.699999);
	TextDrawTextSize(RebootScreenTD[4], 400.000000, 122.000000);
	TextDrawSetOutline(RebootScreenTD[4], 1);
	TextDrawSetShadow(RebootScreenTD[4], 0);
	TextDrawAlignment(RebootScreenTD[4], 2);
	TextDrawColor(RebootScreenTD[4], -1);
	TextDrawBackgroundColor(RebootScreenTD[4], -1);
	TextDrawBoxColor(RebootScreenTD[4], 50);
	TextDrawUseBox(RebootScreenTD[4], 0);
	TextDrawSetProportional(RebootScreenTD[4], 1);
	TextDrawSetSelectable(RebootScreenTD[4], 0);

	RebootScreenTD[5] = TextDrawCreate(550.000000, 319.000000, "ld_dual:white");
	TextDrawFont(RebootScreenTD[5], 4);
	TextDrawLetterSize(RebootScreenTD[5], 0.600000, 2.000000);
	TextDrawTextSize(RebootScreenTD[5], 50.000000, 3.000000);
	TextDrawSetOutline(RebootScreenTD[5], 1);
	TextDrawSetShadow(RebootScreenTD[5], 0);
	TextDrawAlignment(RebootScreenTD[5], 1);
	TextDrawColor(RebootScreenTD[5], 1296911871);
	TextDrawBackgroundColor(RebootScreenTD[5], 255);
	TextDrawBoxColor(RebootScreenTD[5], 50);
	TextDrawUseBox(RebootScreenTD[5], 1);
	TextDrawSetProportional(RebootScreenTD[5], 1);
	TextDrawSetSelectable(RebootScreenTD[5], 0);

	RebootScreenTD[6] = TextDrawCreate(519.000000, 373.000000, "ld_dual:white");
	TextDrawFont(RebootScreenTD[6], 4);
	TextDrawLetterSize(RebootScreenTD[6], 0.600000, 2.000000);
	TextDrawTextSize(RebootScreenTD[6], 3.000000, 15.500000);
	TextDrawSetOutline(RebootScreenTD[6], 1);
	TextDrawSetShadow(RebootScreenTD[6], 0);
	TextDrawAlignment(RebootScreenTD[6], 1);
	TextDrawColor(RebootScreenTD[6], 255);
	TextDrawBackgroundColor(RebootScreenTD[6], 255);
	TextDrawBoxColor(RebootScreenTD[6], 50);
	TextDrawUseBox(RebootScreenTD[6], 1);
	TextDrawSetProportional(RebootScreenTD[6], 1);
	TextDrawSetSelectable(RebootScreenTD[6], 1);
}

CreatePhoneLockScreenTD()
{
    //Player Textdraws
    LockScreenTD[0] = TextDrawCreate(520.500000, 189.399993, "ld_pool:ball");
    TextDrawFont(LockScreenTD[0], 4);
    TextDrawLetterSize(LockScreenTD[0], 0.600000, 2.000000);
    TextDrawTextSize(LockScreenTD[0], 17.000000, 17.000000);
    TextDrawSetOutline(LockScreenTD[0], true);
    TextDrawSetShadow(LockScreenTD[0], false);
    TextDrawAlignment(LockScreenTD[0], true);
    TextDrawColor(LockScreenTD[0], 255);
    TextDrawBackgroundColor(LockScreenTD[0], 255);
    TextDrawBoxColor(LockScreenTD[0], 50);
    TextDrawUseBox(LockScreenTD[0], false);
    TextDrawSetProportional(LockScreenTD[0], true);
    TextDrawSetSelectable(LockScreenTD[0], false);

    LockScreenTD[1] = TextDrawCreate(610.500000, 189.399002, "ld_pool:ball");
    TextDrawFont(LockScreenTD[1], 4);
    TextDrawLetterSize(LockScreenTD[1], 0.600000, 2.000000);
    TextDrawTextSize(LockScreenTD[1], 17.000000, 17.000000);
    TextDrawSetOutline(LockScreenTD[1], true);
    TextDrawSetShadow(LockScreenTD[1], false);
    TextDrawAlignment(LockScreenTD[1], true);
    TextDrawColor(LockScreenTD[1], 255);
    TextDrawBackgroundColor(LockScreenTD[1], 255);
    TextDrawBoxColor(LockScreenTD[1], 50);
    TextDrawUseBox(LockScreenTD[1], false);
    TextDrawSetProportional(LockScreenTD[1], true);
    TextDrawSetSelectable(LockScreenTD[1], false);

    LockScreenTD[2] = TextDrawCreate(610.000000, 416.000000, "ld_pool:ball");
    TextDrawFont(LockScreenTD[2], 4);
    TextDrawLetterSize(LockScreenTD[2], 0.600000, 2.000000);
    TextDrawTextSize(LockScreenTD[2], 17.000000, 17.000000);
    TextDrawSetOutline(LockScreenTD[2], true);
    TextDrawSetShadow(LockScreenTD[2], false);
    TextDrawAlignment(LockScreenTD[2], true);
    TextDrawColor(LockScreenTD[2], 255);
    TextDrawBackgroundColor(LockScreenTD[2], 255);
    TextDrawBoxColor(LockScreenTD[2], 50);
    TextDrawUseBox(LockScreenTD[2], false);
    TextDrawSetProportional(LockScreenTD[2], true);
    TextDrawSetSelectable(LockScreenTD[2], false);

    LockScreenTD[3] = TextDrawCreate(520.500000, 416.000000, "ld_pool:ball");
    TextDrawFont(LockScreenTD[3], 4);
    TextDrawLetterSize(LockScreenTD[3], 0.600000, 2.000000);
    TextDrawTextSize(LockScreenTD[3], 17.000000, 17.000000);
    TextDrawSetOutline(LockScreenTD[3], true);
    TextDrawSetShadow(LockScreenTD[3], false);
    TextDrawAlignment(LockScreenTD[3], true);
    TextDrawColor(LockScreenTD[3], 255);
    TextDrawBackgroundColor(LockScreenTD[3], -8323073);
    TextDrawBoxColor(LockScreenTD[3], 50);
    TextDrawUseBox(LockScreenTD[3], false);
    TextDrawSetProportional(LockScreenTD[3], true);
    TextDrawSetSelectable(LockScreenTD[3], false);

    LockScreenTD[4] = TextDrawCreate(574.000000, 198.000000, "_");
    TextDrawFont(LockScreenTD[4], true);
    TextDrawLetterSize(LockScreenTD[4], 0.600000, 25.099964);
    TextDrawTextSize(LockScreenTD[4], 298.500000, 104.000000);
    TextDrawSetOutline(LockScreenTD[4], true);
    TextDrawSetShadow(LockScreenTD[4], false);
    TextDrawAlignment(LockScreenTD[4], 2);
    TextDrawColor(LockScreenTD[4], -1);
    TextDrawBackgroundColor(LockScreenTD[4], 255);
    TextDrawBoxColor(LockScreenTD[4], 255);
    TextDrawUseBox(LockScreenTD[4], true);
    TextDrawSetProportional(LockScreenTD[4], true);
    TextDrawSetSelectable(LockScreenTD[4], false);

    LockScreenTD[5] = TextDrawCreate(574.000000, 191.000000, "_");
    TextDrawFont(LockScreenTD[5], true);
    TextDrawLetterSize(LockScreenTD[5], 0.608331, 26.649940);
    TextDrawTextSize(LockScreenTD[5], 298.500000, 91.500000);
    TextDrawSetOutline(LockScreenTD[5], true);
    TextDrawSetShadow(LockScreenTD[5], false);
    TextDrawAlignment(LockScreenTD[5], 2);
    TextDrawColor(LockScreenTD[5], 255);
    TextDrawBackgroundColor(LockScreenTD[5], 255);
    TextDrawBoxColor(LockScreenTD[5], 255);
    TextDrawUseBox(LockScreenTD[5], true);
    TextDrawSetProportional(LockScreenTD[5], true);
    TextDrawSetSelectable(LockScreenTD[5], false);

    YellowBoxBackground = TextDrawCreate(574.000000, 208.000000, "_");
    TextDrawFont(YellowBoxBackground, false);
    TextDrawLetterSize(YellowBoxBackground, 0.608331, 22.300006);
    TextDrawTextSize(YellowBoxBackground, 298.500000, 98.000000);
    TextDrawSetOutline(YellowBoxBackground, true);
    TextDrawSetShadow(YellowBoxBackground, false);
    TextDrawAlignment(YellowBoxBackground, 2);
    TextDrawColor(YellowBoxBackground, -1);
    TextDrawBackgroundColor(YellowBoxBackground, 255);
    TextDrawBoxColor(YellowBoxBackground, 0xFFFF00FF);
    TextDrawUseBox(YellowBoxBackground, true);
    TextDrawSetProportional(YellowBoxBackground, true);
    TextDrawSetSelectable(YellowBoxBackground, false);

    RedBoxBackground = TextDrawCreate(574.000000, 208.000000, "_");
    TextDrawFont(RedBoxBackground, false);
    TextDrawLetterSize(RedBoxBackground, 0.608331, 22.300006);
    TextDrawTextSize(RedBoxBackground, 298.500000, 98.000000);
    TextDrawSetOutline(RedBoxBackground, true);
    TextDrawSetShadow(RedBoxBackground, false);
    TextDrawAlignment(RedBoxBackground, 2);
    TextDrawColor(RedBoxBackground, -1);
    TextDrawBackgroundColor(RedBoxBackground, 255);
    TextDrawBoxColor(RedBoxBackground, 0xFF0000FF);
    TextDrawUseBox(RedBoxBackground, true);
    TextDrawSetProportional(RedBoxBackground, true);
    TextDrawSetSelectable(RedBoxBackground, false);

    GreenBoxBackground = TextDrawCreate(574.000000, 208.000000, "_");
    TextDrawFont(GreenBoxBackground, false);
    TextDrawLetterSize(GreenBoxBackground, 0.608331, 22.300006);
    TextDrawTextSize(GreenBoxBackground, 298.500000, 98.000000);
    TextDrawSetOutline(GreenBoxBackground, true);
    TextDrawSetShadow(GreenBoxBackground, false);
    TextDrawAlignment(GreenBoxBackground, 2);
    TextDrawColor(GreenBoxBackground, -1);
    TextDrawBackgroundColor(GreenBoxBackground, 255);
    TextDrawBoxColor(GreenBoxBackground, 0x00AA13FF);
    TextDrawUseBox(GreenBoxBackground, true);
    TextDrawSetProportional(GreenBoxBackground, true);
    TextDrawSetSelectable(GreenBoxBackground, false);

    BlueBoxBackground = TextDrawCreate(574.000000, 208.000000, "_");
    TextDrawFont(BlueBoxBackground, false);
    TextDrawLetterSize(BlueBoxBackground, 0.608331, 22.300006);
    TextDrawTextSize(BlueBoxBackground, 298.500000, 98.000000);
    TextDrawSetOutline(BlueBoxBackground, true);
    TextDrawSetShadow(BlueBoxBackground, false);
    TextDrawAlignment(BlueBoxBackground, 2);
    TextDrawColor(BlueBoxBackground, -1);
    TextDrawBackgroundColor(BlueBoxBackground, 255);
    TextDrawBoxColor(BlueBoxBackground, 0x0047ABFF);
    TextDrawUseBox(BlueBoxBackground, true);
    TextDrawSetProportional(BlueBoxBackground, true);
    TextDrawSetSelectable(BlueBoxBackground, false);

    CyanBoxBackground = TextDrawCreate(574.000000, 208.000000, "_");
    TextDrawFont(CyanBoxBackground, false);
    TextDrawLetterSize(CyanBoxBackground, 0.608331, 22.300006);
    TextDrawTextSize(CyanBoxBackground, 298.500000, 98.000000);
    TextDrawSetOutline(CyanBoxBackground, true);
    TextDrawSetShadow(CyanBoxBackground, false);
    TextDrawAlignment(CyanBoxBackground, 2);
    TextDrawColor(CyanBoxBackground, -1);
    TextDrawBackgroundColor(CyanBoxBackground, 255);
    TextDrawBoxColor(CyanBoxBackground, 0x40E0D0FF);
    TextDrawUseBox(CyanBoxBackground, true);
    TextDrawSetProportional(CyanBoxBackground, true);
    TextDrawSetSelectable(CyanBoxBackground, false);

    PinkBoxBackground = TextDrawCreate(574.000000, 208.000000, "_");
    TextDrawFont(PinkBoxBackground, false);
    TextDrawLetterSize(PinkBoxBackground, 0.608331, 22.300006);
    TextDrawTextSize(PinkBoxBackground, 298.500000, 98.000000);
    TextDrawSetOutline(PinkBoxBackground, true);
    TextDrawSetShadow(PinkBoxBackground, false);
    TextDrawAlignment(PinkBoxBackground, 2);
    TextDrawColor(PinkBoxBackground, -1);
    TextDrawBackgroundColor(PinkBoxBackground, 255);
    TextDrawBoxColor(PinkBoxBackground, -6707969);
    TextDrawUseBox(PinkBoxBackground, true);
    TextDrawSetProportional(PinkBoxBackground, true);
    TextDrawSetSelectable(PinkBoxBackground, false);

    OrangeBoxBackground = TextDrawCreate(574.000000, 208.000000, "_");
    TextDrawFont(OrangeBoxBackground, false);
    TextDrawLetterSize(OrangeBoxBackground, 0.608331, 22.300006);
    TextDrawTextSize(OrangeBoxBackground, 298.500000, 98.000000);
    TextDrawSetOutline(OrangeBoxBackground, true);
    TextDrawSetShadow(OrangeBoxBackground, false);
    TextDrawAlignment(OrangeBoxBackground, 2);
    TextDrawColor(OrangeBoxBackground, -1);
    TextDrawBackgroundColor(OrangeBoxBackground, 255);
    TextDrawBoxColor(OrangeBoxBackground, 0xffb444FF);
    TextDrawUseBox(OrangeBoxBackground, true);
    TextDrawSetProportional(OrangeBoxBackground, true);
    TextDrawSetSelectable(OrangeBoxBackground, false);

    GreyBoxBackground = TextDrawCreate(574.000000, 208.000000, "_");
    TextDrawFont(GreyBoxBackground, false);
    TextDrawLetterSize(GreyBoxBackground, 0.608331, 22.300006);
    TextDrawTextSize(GreyBoxBackground, 298.500000, 98.000000);
    TextDrawSetOutline(GreyBoxBackground, true);
    TextDrawSetShadow(GreyBoxBackground, false);
    TextDrawAlignment(GreyBoxBackground, 2);
    TextDrawColor(GreyBoxBackground, -1);
    TextDrawBackgroundColor(GreyBoxBackground, 255);
    TextDrawBoxColor(GreyBoxBackground, 1296911871);
    TextDrawUseBox(GreyBoxBackground, true);
    TextDrawSetProportional(GreyBoxBackground, true);
    TextDrawSetSelectable(GreyBoxBackground, false);

    CocoBoxBackground = TextDrawCreate(574.000000, 208.000000, "_");
    TextDrawFont(CocoBoxBackground, false);
    TextDrawLetterSize(CocoBoxBackground, 0.608331, 22.300006);
    TextDrawTextSize(CocoBoxBackground, 298.500000, 98.000000);
    TextDrawSetOutline(CocoBoxBackground, true);
    TextDrawSetShadow(CocoBoxBackground, false);
    TextDrawAlignment(CocoBoxBackground, 2);
    TextDrawColor(CocoBoxBackground, -1);
    TextDrawBackgroundColor(CocoBoxBackground, 255);
    TextDrawBoxColor(CocoBoxBackground, 0xa46b14FF);
    TextDrawUseBox(CocoBoxBackground, true);
    TextDrawSetProportional(CocoBoxBackground, true);
    TextDrawSetSelectable(CocoBoxBackground, false);

    CreamBoxBackground = TextDrawCreate(574.000000, 208.000000, "_");
    TextDrawFont(CreamBoxBackground, false);
    TextDrawLetterSize(CreamBoxBackground, 0.608331, 22.300006);
    TextDrawTextSize(CreamBoxBackground, 298.500000, 98.000000);
    TextDrawSetOutline(CreamBoxBackground, true);
    TextDrawSetShadow(CreamBoxBackground, false);
    TextDrawAlignment(CreamBoxBackground, 2);
    TextDrawColor(CreamBoxBackground, -1);
    TextDrawBackgroundColor(CreamBoxBackground, 255);
    TextDrawBoxColor(CreamBoxBackground, 0xe3be9bff);
    TextDrawUseBox(CreamBoxBackground, true);
    TextDrawSetProportional(CreamBoxBackground, true);
    TextDrawSetSelectable(CreamBoxBackground, false);

    HomeButtonPhone[0] = TextDrawCreate(565.500000, 413.000000, "ld_pool:ball"); //tombol home
    TextDrawFont(HomeButtonPhone[0], 4);
    TextDrawLetterSize(HomeButtonPhone[0], 0.600000, 2.000000);
    TextDrawTextSize(HomeButtonPhone[0], 17.000000, 17.000000);
    TextDrawSetOutline(HomeButtonPhone[0], true);
    TextDrawSetShadow(HomeButtonPhone[0], false);
    TextDrawAlignment(HomeButtonPhone[0], true);
    TextDrawColor(HomeButtonPhone[0], 1296911871);
    TextDrawBackgroundColor(HomeButtonPhone[0], 255);
    TextDrawBoxColor(HomeButtonPhone[0], 50);
    TextDrawUseBox(HomeButtonPhone[0], true);
    TextDrawSetProportional(HomeButtonPhone[0], true);
    TextDrawSetSelectable(HomeButtonPhone[0], true);

    HomeButtonPhone[1] = TextDrawCreate(569.000000, 412.000000, "~u~");
    TextDrawFont(HomeButtonPhone[1], true);
    TextDrawLetterSize(HomeButtonPhone[1], 0.633333, 1.549998);
    TextDrawTextSize(HomeButtonPhone[1], 400.000000, 40.500000);
    TextDrawSetOutline(HomeButtonPhone[1], true);
    TextDrawSetShadow(HomeButtonPhone[1], false);
    TextDrawAlignment(HomeButtonPhone[1], 2);
    TextDrawColor(HomeButtonPhone[1], -1);
    TextDrawBackgroundColor(HomeButtonPhone[1], 255);
    TextDrawBoxColor(HomeButtonPhone[1], 50);
    TextDrawUseBox(HomeButtonPhone[1], false);
    TextDrawSetProportional(HomeButtonPhone[1], true);
    TextDrawSetSelectable(HomeButtonPhone[1], false);

    LockScreenTD[6] = TextDrawCreate(575.000000, 261.000000, "10:15");
    TextDrawFont(LockScreenTD[6], true);
    TextDrawLetterSize(LockScreenTD[6], 0.391665, 2.000000);
    TextDrawTextSize(LockScreenTD[6], 400.000000, 122.000000);
    TextDrawSetOutline(LockScreenTD[6], false);
    TextDrawSetShadow(LockScreenTD[6], false);
    TextDrawAlignment(LockScreenTD[6], 2);
    TextDrawColor(LockScreenTD[6], -1);
    TextDrawBackgroundColor(LockScreenTD[6], 255);
    TextDrawBoxColor(LockScreenTD[6], 50);
    TextDrawUseBox(LockScreenTD[6], false);
    TextDrawSetProportional(LockScreenTD[6], true);
    TextDrawSetSelectable(LockScreenTD[6], false);

    LockScreenTD[7] = TextDrawCreate(575.000000, 280.000000, "Jum, 30 September 2022");
    TextDrawFont(LockScreenTD[7], true);
    TextDrawLetterSize(LockScreenTD[7], 0.129166, 1.049999);
    TextDrawTextSize(LockScreenTD[7], 400.000000, 122.000000);
    TextDrawSetOutline(LockScreenTD[7], false);
    TextDrawSetShadow(LockScreenTD[7], false);
    TextDrawAlignment(LockScreenTD[7], 2);
    TextDrawColor(LockScreenTD[7], -1);
    TextDrawBackgroundColor(LockScreenTD[7], 255);
    TextDrawBoxColor(LockScreenTD[7], 50);
    TextDrawUseBox(LockScreenTD[7], false);
    TextDrawSetProportional(LockScreenTD[7], true);
    TextDrawSetSelectable(LockScreenTD[7], false);

    FingerButtonPhone = TextDrawCreate(565.500000, 374.000000, "ld_pool:ball"); //tombol finger print
    TextDrawFont(FingerButtonPhone, 4);
    TextDrawLetterSize(FingerButtonPhone, 0.600000, 2.000000);
    TextDrawTextSize(FingerButtonPhone, 17.000000, 17.000000);
    TextDrawSetOutline(FingerButtonPhone, true);
    TextDrawSetShadow(FingerButtonPhone, false);
    TextDrawAlignment(FingerButtonPhone, true);
    TextDrawColor(FingerButtonPhone, -168436481);
    TextDrawBackgroundColor(FingerButtonPhone, 255);
    TextDrawBoxColor(FingerButtonPhone, 50);
    TextDrawUseBox(FingerButtonPhone, true);
    TextDrawSetProportional(FingerButtonPhone, true);
    TextDrawSetSelectable(FingerButtonPhone, true);

    LockScreenTD[8] = TextDrawCreate(574.000000, 191.000000, "iPhone");
    TextDrawFont(LockScreenTD[8], true);
    TextDrawLetterSize(LockScreenTD[8], 0.220833, 1.250000);
    TextDrawTextSize(LockScreenTD[8], 400.000000, 97.000000);
    TextDrawSetOutline(LockScreenTD[8], false);
    TextDrawSetShadow(LockScreenTD[8], true);
    TextDrawAlignment(LockScreenTD[8], 2);
    TextDrawColor(LockScreenTD[8], -1);
    TextDrawBackgroundColor(LockScreenTD[8], 255);
    TextDrawBoxColor(LockScreenTD[8], 50);
    TextDrawUseBox(LockScreenTD[8], false);
    TextDrawSetProportional(LockScreenTD[8], true);
    TextDrawSetSelectable(LockScreenTD[8], false);

    LockScreenTD[9] = TextDrawCreate(609.500000, 193.000000, "ld_pool:ball");
    TextDrawFont(LockScreenTD[9], 4);
    TextDrawLetterSize(LockScreenTD[9], 0.600000, 2.000000);
    TextDrawTextSize(LockScreenTD[9], 5.000000, 5.500000);
    TextDrawSetOutline(LockScreenTD[9], true);
    TextDrawSetShadow(LockScreenTD[9], false);
    TextDrawAlignment(LockScreenTD[9], true);
    TextDrawColor(LockScreenTD[9], -1);
    TextDrawBackgroundColor(LockScreenTD[9], 255);
    TextDrawBoxColor(LockScreenTD[9], 50);
    TextDrawUseBox(LockScreenTD[9], true);
    TextDrawSetProportional(LockScreenTD[9], true);
    TextDrawSetSelectable(LockScreenTD[9], false);

    LockScreenTD[10] = TextDrawCreate(610.500000, 194.000000, "ld_pool:ball");
    TextDrawFont(LockScreenTD[10], 4);
    TextDrawLetterSize(LockScreenTD[10], 0.600000, 2.000000);
    TextDrawTextSize(LockScreenTD[10], 2.500000, 2.500000);
    TextDrawSetOutline(LockScreenTD[10], true);
    TextDrawSetShadow(LockScreenTD[10], false);
    TextDrawAlignment(LockScreenTD[10], true);
    TextDrawColor(LockScreenTD[10], 255);
    TextDrawBackgroundColor(LockScreenTD[10], 255);
    TextDrawBoxColor(LockScreenTD[10], 50);
    TextDrawUseBox(LockScreenTD[10], true);
    TextDrawSetProportional(LockScreenTD[10], true);
    TextDrawSetSelectable(LockScreenTD[10], false);
}

CreatePhoneMainMenuTD()
{
    MainMenuTD[0] = TextDrawCreate(543.299987, 233.000000, "_");
    TextDrawFont(MainMenuTD[0], false);
    TextDrawLetterSize(MainMenuTD[0], 0.608331, 2.400005);
    TextDrawTextSize(MainMenuTD[0], 298.500000, 19.000000);
    TextDrawSetOutline(MainMenuTD[0], true);
    TextDrawSetShadow(MainMenuTD[0], false);
    TextDrawAlignment(MainMenuTD[0], 2);
    TextDrawColor(MainMenuTD[0], -1);
    TextDrawBackgroundColor(MainMenuTD[0], 255);
    TextDrawBoxColor(MainMenuTD[0], 9109759);
    TextDrawUseBox(MainMenuTD[0], true);
    TextDrawSetProportional(MainMenuTD[0], true);
    TextDrawSetSelectable(MainMenuTD[0], false);

    KontakButtonPhone = TextDrawCreate(535.000000, 235.000000, "HUD:radar_savegame");
    TextDrawFont(KontakButtonPhone, 4);
    TextDrawLetterSize(KontakButtonPhone, 0.600000, 2.000000);
    TextDrawTextSize(KontakButtonPhone, 17.000000, 17.000000);
    TextDrawSetOutline(KontakButtonPhone, true);
    TextDrawSetShadow(KontakButtonPhone, false);
    TextDrawAlignment(KontakButtonPhone, true);
    TextDrawColor(KontakButtonPhone, -1);
    TextDrawBackgroundColor(KontakButtonPhone, 255);
    TextDrawBoxColor(KontakButtonPhone, 50);
    TextDrawUseBox(KontakButtonPhone, false);
    TextDrawSetProportional(KontakButtonPhone, true);
    TextDrawSetSelectable(KontakButtonPhone, true);

    MainMenuTD[1] = TextDrawCreate(543.000000, 256.000000, "Kontak");
    TextDrawFont(MainMenuTD[1], true);
    TextDrawLetterSize(MainMenuTD[1], 0.162498, 1.049998);
    TextDrawTextSize(MainMenuTD[1], 400.000000, 122.000000);
    TextDrawSetOutline(MainMenuTD[1], false);
    TextDrawSetShadow(MainMenuTD[1], false);
    TextDrawAlignment(MainMenuTD[1], 2);
    TextDrawColor(MainMenuTD[1], -1);
    TextDrawBackgroundColor(MainMenuTD[1], 255);
    TextDrawBoxColor(MainMenuTD[1], 50);
    TextDrawUseBox(MainMenuTD[1], false);
    TextDrawSetProportional(MainMenuTD[1], true);
    TextDrawSetSelectable(MainMenuTD[1], false);

    MainMenuTD[2] = TextDrawCreate(573.599975, 233.000000, "_");
    TextDrawFont(MainMenuTD[2], false);
    TextDrawLetterSize(MainMenuTD[2], 0.608331, 2.400005);
    TextDrawTextSize(MainMenuTD[2], 298.500000, 19.000000);
    TextDrawSetOutline(MainMenuTD[2], true);
    TextDrawSetShadow(MainMenuTD[2], false);
    TextDrawAlignment(MainMenuTD[2], 2);
    TextDrawColor(MainMenuTD[2], -1);
    TextDrawBackgroundColor(MainMenuTD[2], 255);
    TextDrawBoxColor(MainMenuTD[2], -1094795521);
    TextDrawUseBox(MainMenuTD[2], true);
    TextDrawSetProportional(MainMenuTD[2], true);
    TextDrawSetSelectable(MainMenuTD[2], false);

    GPSButtonPhone = TextDrawCreate(565.500000, 235.000000, "HUD:radar_waypoint");
    TextDrawFont(GPSButtonPhone, 4);
    TextDrawLetterSize(GPSButtonPhone, 0.600000, 2.000000);
    TextDrawTextSize(GPSButtonPhone, 17.000000, 17.000000);
    TextDrawSetOutline(GPSButtonPhone, true);
    TextDrawSetShadow(GPSButtonPhone, false);
    TextDrawAlignment(GPSButtonPhone, true);
    TextDrawColor(GPSButtonPhone, -1);
    TextDrawBackgroundColor(GPSButtonPhone, 255);
    TextDrawBoxColor(GPSButtonPhone, 50);
    TextDrawUseBox(GPSButtonPhone, false);
    TextDrawSetProportional(GPSButtonPhone, true);
    TextDrawSetSelectable(GPSButtonPhone, true);

    MainMenuTD[3] = TextDrawCreate(573.500000, 256.000000, "GPS");
    TextDrawFont(MainMenuTD[3], true);
    TextDrawLetterSize(MainMenuTD[3], 0.162498, 1.049998);
    TextDrawTextSize(MainMenuTD[3], 400.000000, 122.000000);
    TextDrawSetOutline(MainMenuTD[3], false);
    TextDrawSetShadow(MainMenuTD[3], false);
    TextDrawAlignment(MainMenuTD[3], 2);
    TextDrawColor(MainMenuTD[3], -1);
    TextDrawBackgroundColor(MainMenuTD[3], 255);
    TextDrawBoxColor(MainMenuTD[3], 50);
    TextDrawUseBox(MainMenuTD[3], false);
    TextDrawSetProportional(MainMenuTD[3], true);
    TextDrawSetSelectable(MainMenuTD[3], false);

    MainMenuTD[4] = TextDrawCreate(604.500000, 233.000000, "_");
    TextDrawFont(MainMenuTD[4], false);
    TextDrawLetterSize(MainMenuTD[4], 0.608331, 2.400005);
    TextDrawTextSize(MainMenuTD[4], 298.500000, 19.000000);
    TextDrawSetOutline(MainMenuTD[4], true);
    TextDrawSetShadow(MainMenuTD[4], false);
    TextDrawAlignment(MainMenuTD[4], 2);
    TextDrawColor(MainMenuTD[4], -1);
    TextDrawBackgroundColor(MainMenuTD[4], 255);
    TextDrawBoxColor(MainMenuTD[4], -1104226561);
    TextDrawUseBox(MainMenuTD[4], true);
    TextDrawSetProportional(MainMenuTD[4], true);
    TextDrawSetSelectable(MainMenuTD[4], false);

    AirdropButtonPhone = TextDrawCreate(596.000000, 235.000000, "HUD:radar_triadscasino");
    TextDrawFont(AirdropButtonPhone, 4);
    TextDrawLetterSize(AirdropButtonPhone, 0.600000, 2.000000);
    TextDrawTextSize(AirdropButtonPhone, 17.000000, 17.000000);
    TextDrawSetOutline(AirdropButtonPhone, true);
    TextDrawSetShadow(AirdropButtonPhone, false);
    TextDrawAlignment(AirdropButtonPhone, true);
    TextDrawColor(AirdropButtonPhone, -1);
    TextDrawBackgroundColor(AirdropButtonPhone, 255);
    TextDrawBoxColor(AirdropButtonPhone, 50);
    TextDrawUseBox(AirdropButtonPhone, true);
    TextDrawSetProportional(AirdropButtonPhone, true);
    TextDrawSetSelectable(AirdropButtonPhone, true);

    MainMenuTD[5] = TextDrawCreate(604.500000, 256.000000, "Airdrop");
    TextDrawFont(MainMenuTD[5], true);
    TextDrawLetterSize(MainMenuTD[5], 0.162498, 1.049998);
    TextDrawTextSize(MainMenuTD[5], 400.000000, 122.000000);
    TextDrawSetOutline(MainMenuTD[5], false);
    TextDrawSetShadow(MainMenuTD[5], false);
    TextDrawAlignment(MainMenuTD[5], 2);
    TextDrawColor(MainMenuTD[5], -1);
    TextDrawBackgroundColor(MainMenuTD[5], 255);
    TextDrawBoxColor(MainMenuTD[5], 50);
    TextDrawUseBox(MainMenuTD[5], false);
    TextDrawSetProportional(MainMenuTD[5], true);
    TextDrawSetSelectable(MainMenuTD[5], false);

    MainMenuTD[6] = TextDrawCreate(543.299987, 275.000000, "_");
    TextDrawFont(MainMenuTD[6], false);
    TextDrawLetterSize(MainMenuTD[6], 0.608331, 2.400005);
    TextDrawTextSize(MainMenuTD[6], 298.500000, 19.000000);
    TextDrawSetOutline(MainMenuTD[6], true);
    TextDrawSetShadow(MainMenuTD[6], false);
    TextDrawAlignment(MainMenuTD[6], 2);
    TextDrawColor(MainMenuTD[6], -1);
    TextDrawBackgroundColor(MainMenuTD[6], 255);
    TextDrawBoxColor(MainMenuTD[6], 1296911871);
    TextDrawUseBox(MainMenuTD[6], true);
    TextDrawSetProportional(MainMenuTD[6], true);
    TextDrawSetSelectable(MainMenuTD[6], false);

    BankingButtonPhone = TextDrawCreate(535.000000, 277.000000, "ld_card:cdback");
    TextDrawFont(BankingButtonPhone, 4);
    TextDrawLetterSize(BankingButtonPhone, 0.600000, 2.000000);
    TextDrawTextSize(BankingButtonPhone, 17.000000, 17.000000);
    TextDrawSetOutline(BankingButtonPhone, true);
    TextDrawSetShadow(BankingButtonPhone, false);
    TextDrawAlignment(BankingButtonPhone, true);
    TextDrawColor(BankingButtonPhone, -1);
    TextDrawBackgroundColor(BankingButtonPhone, 255);
    TextDrawBoxColor(BankingButtonPhone, 50);
    TextDrawUseBox(BankingButtonPhone, true);
    TextDrawSetProportional(BankingButtonPhone, true);
    TextDrawSetSelectable(BankingButtonPhone, true);

    MainMenuTD[7] = TextDrawCreate(543.500000, 298.000000, "Banking");
    TextDrawFont(MainMenuTD[7], true);
    TextDrawLetterSize(MainMenuTD[7], 0.162498, 1.049998);
    TextDrawTextSize(MainMenuTD[7], 400.000000, 122.000000);
    TextDrawSetOutline(MainMenuTD[7], false);
    TextDrawSetShadow(MainMenuTD[7], false);
    TextDrawAlignment(MainMenuTD[7], 2);
    TextDrawColor(MainMenuTD[7], -1);
    TextDrawBackgroundColor(MainMenuTD[7], 255);
    TextDrawBoxColor(MainMenuTD[7], 50);
    TextDrawUseBox(MainMenuTD[7], false);
    TextDrawSetProportional(MainMenuTD[7], true);
    TextDrawSetSelectable(MainMenuTD[7], false);

    MainMenuTD[8] = TextDrawCreate(573.599975, 275.000000, "_");
    TextDrawFont(MainMenuTD[8], false);
    TextDrawLetterSize(MainMenuTD[8], 0.608331, 2.400005);
    TextDrawTextSize(MainMenuTD[8], 298.500000, 19.000000);
    TextDrawSetOutline(MainMenuTD[8], true);
    TextDrawSetShadow(MainMenuTD[8], false);
    TextDrawAlignment(MainMenuTD[8], 2);
    TextDrawColor(MainMenuTD[8], -1);
    TextDrawBackgroundColor(MainMenuTD[8], 255);
    TextDrawBoxColor(MainMenuTD[8], 1097458175);
    TextDrawUseBox(MainMenuTD[8], true);
    TextDrawSetProportional(MainMenuTD[8], true);
    TextDrawSetSelectable(MainMenuTD[8], false);

    AppStoreButtonPhone = TextDrawCreate(565.000000, 277.000000, "HUD:radar_airyard");
    TextDrawFont(AppStoreButtonPhone, 4);
    TextDrawLetterSize(AppStoreButtonPhone, 0.600000, 2.000000);
    TextDrawTextSize(AppStoreButtonPhone, 17.000000, 17.000000);
    TextDrawSetOutline(AppStoreButtonPhone, true);
    TextDrawSetShadow(AppStoreButtonPhone, false);
    TextDrawAlignment(AppStoreButtonPhone, true);
    TextDrawColor(AppStoreButtonPhone, -1);
    TextDrawBackgroundColor(AppStoreButtonPhone, 255);
    TextDrawBoxColor(AppStoreButtonPhone, 50);
    TextDrawUseBox(AppStoreButtonPhone, true);
    TextDrawSetProportional(AppStoreButtonPhone, true);
    TextDrawSetSelectable(AppStoreButtonPhone, true);

    MainMenuTD[9] = TextDrawCreate(573.500000, 298.000000, "AppStore");
    TextDrawFont(MainMenuTD[9], true);
    TextDrawLetterSize(MainMenuTD[9], 0.162498, 1.049998);
    TextDrawTextSize(MainMenuTD[9], 400.000000, 122.000000);
    TextDrawSetOutline(MainMenuTD[9], false);
    TextDrawSetShadow(MainMenuTD[9], false);
    TextDrawAlignment(MainMenuTD[9], 2);
    TextDrawColor(MainMenuTD[9], -1);
    TextDrawBackgroundColor(MainMenuTD[9], 255);
    TextDrawBoxColor(MainMenuTD[9], 50);
    TextDrawUseBox(MainMenuTD[9], false);
    TextDrawSetProportional(MainMenuTD[9], true);
    TextDrawSetSelectable(MainMenuTD[9], false);

    MainMenuTD[10] = TextDrawCreate(604.500000, 275.000000, "_");
    TextDrawFont(MainMenuTD[10], false);
    TextDrawLetterSize(MainMenuTD[10], 0.608331, 2.400005);
    TextDrawTextSize(MainMenuTD[10], 298.500000, 19.000000);
    TextDrawSetOutline(MainMenuTD[10], true);
    TextDrawSetShadow(MainMenuTD[10], false);
    TextDrawAlignment(MainMenuTD[10], 2);
    TextDrawColor(MainMenuTD[10], -1);
    TextDrawBackgroundColor(MainMenuTD[10], 255);
    TextDrawBoxColor(MainMenuTD[10], -1);
    TextDrawUseBox(MainMenuTD[10], true);
    TextDrawSetProportional(MainMenuTD[10], true);
    TextDrawSetSelectable(MainMenuTD[10], false);

    SettingsButtonPhone = TextDrawCreate(596.000000, 277.000000, "ld_beat:upl");
    TextDrawFont(SettingsButtonPhone, 4);
    TextDrawLetterSize(SettingsButtonPhone, 0.600000, 2.000000);
    TextDrawTextSize(SettingsButtonPhone, 17.000000, 17.000000);
    TextDrawSetOutline(SettingsButtonPhone, true);
    TextDrawSetShadow(SettingsButtonPhone, false);
    TextDrawAlignment(SettingsButtonPhone, true);
    TextDrawColor(SettingsButtonPhone, -1061109505);
    TextDrawBackgroundColor(SettingsButtonPhone, 255);
    TextDrawBoxColor(SettingsButtonPhone, 50);
    TextDrawUseBox(SettingsButtonPhone, true);
    TextDrawSetProportional(SettingsButtonPhone, true);
    TextDrawSetSelectable(SettingsButtonPhone, true);

    MainMenuTD[11] = TextDrawCreate(604.500000, 298.000000, "Settings");
    TextDrawFont(MainMenuTD[11], true);
    TextDrawLetterSize(MainMenuTD[11], 0.162498, 1.049998);
    TextDrawTextSize(MainMenuTD[11], 400.000000, 122.000000);
    TextDrawSetOutline(MainMenuTD[11], false);
    TextDrawSetShadow(MainMenuTD[11], false);
    TextDrawAlignment(MainMenuTD[11], 2);
    TextDrawColor(MainMenuTD[11], -1);
    TextDrawBackgroundColor(MainMenuTD[11], 255);
    TextDrawBoxColor(MainMenuTD[11], 50);
    TextDrawUseBox(MainMenuTD[11], false);
    TextDrawSetProportional(MainMenuTD[11], true);
    TextDrawSetSelectable(MainMenuTD[11], false);

    MainMenuTD[12] = TextDrawCreate(604.500000, 361.000000, "_");
    TextDrawFont(MainMenuTD[12], false);
    TextDrawLetterSize(MainMenuTD[12], 0.608331, 2.400005);
    TextDrawTextSize(MainMenuTD[12], 298.500000, 19.000000);
    TextDrawSetOutline(MainMenuTD[12], true);
    TextDrawSetShadow(MainMenuTD[12], false);
    TextDrawAlignment(MainMenuTD[12], 2);
    TextDrawColor(MainMenuTD[12], -1);
    TextDrawBackgroundColor(MainMenuTD[12], 255);
    TextDrawBoxColor(MainMenuTD[12], 9145343);
    TextDrawUseBox(MainMenuTD[12], true);
    TextDrawSetProportional(MainMenuTD[12], true);
    TextDrawSetSelectable(MainMenuTD[12], false);

    CallButtonPhone = TextDrawCreate(596.000000, 363.000000, "ld_chat:badchat");
    TextDrawFont(CallButtonPhone, 4);
    TextDrawLetterSize(CallButtonPhone, 0.600000, 2.000000);
    TextDrawTextSize(CallButtonPhone, 17.000000, 17.000000);
    TextDrawSetOutline(CallButtonPhone, true);
    TextDrawSetShadow(CallButtonPhone, false);
    TextDrawAlignment(CallButtonPhone, true);
    TextDrawColor(CallButtonPhone, -1);
    TextDrawBackgroundColor(CallButtonPhone, 255);
    TextDrawBoxColor(CallButtonPhone, 50);
    TextDrawUseBox(CallButtonPhone, true);
    TextDrawSetProportional(CallButtonPhone, true);
    TextDrawSetSelectable(CallButtonPhone, true);

    MainMenuTD[13] = TextDrawCreate(604.500000, 384.000000, "Call");
    TextDrawFont(MainMenuTD[13], true);
    TextDrawLetterSize(MainMenuTD[13], 0.162497, 1.049998);
    TextDrawTextSize(MainMenuTD[13], 400.000000, 122.000000);
    TextDrawSetOutline(MainMenuTD[13], false);
    TextDrawSetShadow(MainMenuTD[13], false);
    TextDrawAlignment(MainMenuTD[13], 2);
    TextDrawColor(MainMenuTD[13], -1);
    TextDrawBackgroundColor(MainMenuTD[13], 255);
    TextDrawBoxColor(MainMenuTD[13], 50);
    TextDrawUseBox(MainMenuTD[13], false);
    TextDrawSetProportional(MainMenuTD[13], true);
    TextDrawSetSelectable(MainMenuTD[13], false);

    WhatsappButtonPhone[0] = TextDrawCreate(543.299987, 318.000000, "_");
    TextDrawFont(WhatsappButtonPhone[0], false);
    TextDrawLetterSize(WhatsappButtonPhone[0], 0.608331, 2.400005);
    TextDrawTextSize(WhatsappButtonPhone[0], 298.500000, 19.000000);
    TextDrawSetOutline(WhatsappButtonPhone[0], true);
    TextDrawSetShadow(WhatsappButtonPhone[0], false);
    TextDrawAlignment(WhatsappButtonPhone[0], 2);
    TextDrawColor(WhatsappButtonPhone[0], -1);
    TextDrawBackgroundColor(WhatsappButtonPhone[0], 255);
    TextDrawBoxColor(WhatsappButtonPhone[0], 2094792959);
    TextDrawUseBox(WhatsappButtonPhone[0], true);
    TextDrawSetProportional(WhatsappButtonPhone[0], true);
    TextDrawSetSelectable(WhatsappButtonPhone[0], false);

    WhatsappButtonPhone[1] = TextDrawCreate(535.000000, 320.000000, "ld_chat:goodcha");
    TextDrawFont(WhatsappButtonPhone[1], 4);
    TextDrawLetterSize(WhatsappButtonPhone[1], 0.600000, 2.000000);
    TextDrawTextSize(WhatsappButtonPhone[1], 17.000000, 17.000000);
    TextDrawSetOutline(WhatsappButtonPhone[1], true);
    TextDrawSetShadow(WhatsappButtonPhone[1], false);
    TextDrawAlignment(WhatsappButtonPhone[1], true);
    TextDrawColor(WhatsappButtonPhone[1], -1);
    TextDrawBackgroundColor(WhatsappButtonPhone[1], 255);
    TextDrawBoxColor(WhatsappButtonPhone[1], 50);
    TextDrawUseBox(WhatsappButtonPhone[1], true);
    TextDrawSetProportional(WhatsappButtonPhone[1], true);
    TextDrawSetSelectable(WhatsappButtonPhone[1], true);

    WhatsappButtonPhone[2] = TextDrawCreate(543.500000, 341.000000, "WhatsApp");
    TextDrawFont(WhatsappButtonPhone[2], true);
    TextDrawLetterSize(WhatsappButtonPhone[2], 0.162498, 1.049998);
    TextDrawTextSize(WhatsappButtonPhone[2], 400.000000, 122.000000);
    TextDrawSetOutline(WhatsappButtonPhone[2], false);
    TextDrawSetShadow(WhatsappButtonPhone[2], false);
    TextDrawAlignment(WhatsappButtonPhone[2], 2);
    TextDrawColor(WhatsappButtonPhone[2], -1);
    TextDrawBackgroundColor(WhatsappButtonPhone[2], 255);
    TextDrawBoxColor(WhatsappButtonPhone[2], 50);
    TextDrawUseBox(WhatsappButtonPhone[2], false);
    TextDrawSetProportional(WhatsappButtonPhone[2], true);
    TextDrawSetSelectable(WhatsappButtonPhone[2], false);

    SpotifyButtonPhone[0] = TextDrawCreate(573.599975, 318.000000, "_");
    TextDrawFont(SpotifyButtonPhone[0], false);
    TextDrawLetterSize(SpotifyButtonPhone[0], 0.608331, 2.400005);
    TextDrawTextSize(SpotifyButtonPhone[0], 298.500000, 19.000000);
    TextDrawSetOutline(SpotifyButtonPhone[0], true);
    TextDrawSetShadow(SpotifyButtonPhone[0], false);
    TextDrawAlignment(SpotifyButtonPhone[0], 2);
    TextDrawColor(SpotifyButtonPhone[0], -1);
    TextDrawBackgroundColor(SpotifyButtonPhone[0], 255);
    TextDrawBoxColor(SpotifyButtonPhone[0], 255);
    TextDrawUseBox(SpotifyButtonPhone[0], true);
    TextDrawSetProportional(SpotifyButtonPhone[0], true);
    TextDrawSetSelectable(SpotifyButtonPhone[0], false);

    SpotifyButtonPhone[1] = TextDrawCreate(565.500000, 320.000000, "HUD:radar_datedisco");
    TextDrawFont(SpotifyButtonPhone[1], 4);
    TextDrawLetterSize(SpotifyButtonPhone[1], 0.600000, 2.000000);
    TextDrawTextSize(SpotifyButtonPhone[1], 17.000000, 17.000000);
    TextDrawSetOutline(SpotifyButtonPhone[1], true);
    TextDrawSetShadow(SpotifyButtonPhone[1], false);
    TextDrawAlignment(SpotifyButtonPhone[1], true);
    TextDrawColor(SpotifyButtonPhone[1], 16711935);
    TextDrawBackgroundColor(SpotifyButtonPhone[1], 255);
    TextDrawBoxColor(SpotifyButtonPhone[1], 50);
    TextDrawUseBox(SpotifyButtonPhone[1], true);
    TextDrawSetProportional(SpotifyButtonPhone[1], true);
    TextDrawSetSelectable(SpotifyButtonPhone[1], true);

    SpotifyButtonPhone[2] = TextDrawCreate(573.500000, 341.000000, "Spotify");
    TextDrawFont(SpotifyButtonPhone[2], true);
    TextDrawLetterSize(SpotifyButtonPhone[2], 0.162498, 1.049998);
    TextDrawTextSize(SpotifyButtonPhone[2], 400.000000, 122.000000);
    TextDrawSetOutline(SpotifyButtonPhone[2], false);
    TextDrawSetShadow(SpotifyButtonPhone[2], false);
    TextDrawAlignment(SpotifyButtonPhone[2], 2);
    TextDrawColor(SpotifyButtonPhone[2], -1);
    TextDrawBackgroundColor(SpotifyButtonPhone[2], 255);
    TextDrawBoxColor(SpotifyButtonPhone[2], 50);
    TextDrawUseBox(SpotifyButtonPhone[2], false);
    TextDrawSetProportional(SpotifyButtonPhone[2], true);
    TextDrawSetSelectable(SpotifyButtonPhone[2], false);

    TwitterButtonPhone[0] = TextDrawCreate(604.500000, 318.000000, "_");
    TextDrawFont(TwitterButtonPhone[0], false);
    TextDrawLetterSize(TwitterButtonPhone[0], 0.608331, 2.400005);
    TextDrawTextSize(TwitterButtonPhone[0], 298.500000, 19.000000);
    TextDrawSetOutline(TwitterButtonPhone[0], true);
    TextDrawSetShadow(TwitterButtonPhone[0], false);
    TextDrawAlignment(TwitterButtonPhone[0], 2);
    TextDrawColor(TwitterButtonPhone[0], -1);
    TextDrawBackgroundColor(TwitterButtonPhone[0], 255);
    TextDrawBoxColor(TwitterButtonPhone[0], 11333375);
    TextDrawUseBox(TwitterButtonPhone[0], true);
    TextDrawSetProportional(TwitterButtonPhone[0], true);
    TextDrawSetSelectable(TwitterButtonPhone[0], false);

    TwitterButtonPhone[1] = TextDrawCreate(596.000000, 319.000000, "ld_grav:beea");
    TextDrawFont(TwitterButtonPhone[1], 4);
    TextDrawLetterSize(TwitterButtonPhone[1], 0.600000, 2.000000);
    TextDrawTextSize(TwitterButtonPhone[1], 17.000000, 17.000000);
    TextDrawSetOutline(TwitterButtonPhone[1], true);
    TextDrawSetShadow(TwitterButtonPhone[1], false);
    TextDrawAlignment(TwitterButtonPhone[1], true);
    TextDrawColor(TwitterButtonPhone[1], -1);
    TextDrawBackgroundColor(TwitterButtonPhone[1], 255);
    TextDrawBoxColor(TwitterButtonPhone[1], 50);
    TextDrawUseBox(TwitterButtonPhone[1], true);
    TextDrawSetProportional(TwitterButtonPhone[1], true);
    TextDrawSetSelectable(TwitterButtonPhone[1], true);

    TwitterButtonPhone[2] = TextDrawCreate(604.500000, 341.000000, "Twitter");
    TextDrawFont(TwitterButtonPhone[2], true);
    TextDrawLetterSize(TwitterButtonPhone[2], 0.162498, 1.049998);
    TextDrawTextSize(TwitterButtonPhone[2], 400.000000, 122.000000);
    TextDrawSetOutline(TwitterButtonPhone[2], false);
    TextDrawSetShadow(TwitterButtonPhone[2], false);
    TextDrawAlignment(TwitterButtonPhone[2], 2);
    TextDrawColor(TwitterButtonPhone[2], -1);
    TextDrawBackgroundColor(TwitterButtonPhone[2], 255);
    TextDrawBoxColor(TwitterButtonPhone[2], 50);
    TextDrawUseBox(TwitterButtonPhone[2], false);
    TextDrawSetProportional(TwitterButtonPhone[2], true);
    TextDrawSetSelectable(TwitterButtonPhone[2], false);

    UberButtonPhone[0] = TextDrawCreate(543.299987, 361.000000, "_");
    TextDrawFont(UberButtonPhone[0], 0);
    TextDrawLetterSize(UberButtonPhone[0], 0.608331, 2.400005);
    TextDrawTextSize(UberButtonPhone[0], 298.500000, 19.000000);
    TextDrawSetOutline(UberButtonPhone[0], 1);
    TextDrawSetShadow(UberButtonPhone[0], 0);
    TextDrawAlignment(UberButtonPhone[0], 2);
    TextDrawColor(UberButtonPhone[0], -1);
    TextDrawBackgroundColor(UberButtonPhone[0], 255);
    TextDrawBoxColor(UberButtonPhone[0], -1);
    TextDrawUseBox(UberButtonPhone[0], 1);
    TextDrawSetProportional(UberButtonPhone[0], 1);
    TextDrawSetSelectable(UberButtonPhone[0], 0);

    UberButtonPhone[1] = TextDrawCreate(535.000000, 363.000000, "HUD:radar_triadscasino");
    TextDrawFont(UberButtonPhone[1], 4);
    TextDrawLetterSize(UberButtonPhone[1], 0.600000, 2.000000);
    TextDrawTextSize(UberButtonPhone[1], 17.000000, 17.000000);
    TextDrawSetOutline(UberButtonPhone[1], 1);
    TextDrawSetShadow(UberButtonPhone[1], 0);
    TextDrawAlignment(UberButtonPhone[1], 1);
    TextDrawColor(UberButtonPhone[1], -1094795521);
    TextDrawBackgroundColor(UberButtonPhone[1], 255);
    TextDrawBoxColor(UberButtonPhone[1], 50);
    TextDrawUseBox(UberButtonPhone[1], 1);
    TextDrawSetProportional(UberButtonPhone[1], 1);
    TextDrawSetSelectable(UberButtonPhone[1], 1);

    UberButtonPhone[2] = TextDrawCreate(543.500000, 384.000000, "Uber");
    TextDrawFont(UberButtonPhone[2], 1);
    TextDrawLetterSize(UberButtonPhone[2], 0.162498, 1.049998);
    TextDrawTextSize(UberButtonPhone[2], 400.000000, 122.000000);
    TextDrawSetOutline(UberButtonPhone[2], 0);
    TextDrawSetShadow(UberButtonPhone[2], 0);
    TextDrawAlignment(UberButtonPhone[2], 2);
    TextDrawColor(UberButtonPhone[2], -1);
    TextDrawBackgroundColor(UberButtonPhone[2], 255);
    TextDrawBoxColor(UberButtonPhone[2], 50);
    TextDrawUseBox(UberButtonPhone[2], 0);
    TextDrawSetProportional(UberButtonPhone[2], 1);
    TextDrawSetSelectable(UberButtonPhone[2], 0);

    YellowButtonPhone[0] = TextDrawCreate(573.599975, 361.000000, "_");
    TextDrawFont(YellowButtonPhone[0], false);
    TextDrawLetterSize(YellowButtonPhone[0], 0.608331, 2.400005);
    TextDrawTextSize(YellowButtonPhone[0], 298.500000, 19.000000);
    TextDrawSetOutline(YellowButtonPhone[0], true);
    TextDrawSetShadow(YellowButtonPhone[0], false);
    TextDrawAlignment(YellowButtonPhone[0], 2);
    TextDrawColor(YellowButtonPhone[0], -1);
    TextDrawBackgroundColor(YellowButtonPhone[0], 255);
    TextDrawBoxColor(YellowButtonPhone[0], -2686721);
    TextDrawUseBox(YellowButtonPhone[0], true);
    TextDrawSetProportional(YellowButtonPhone[0], true);
    TextDrawSetSelectable(YellowButtonPhone[0], false);

    YellowButtonPhone[1] = TextDrawCreate(565.000000, 363.000000, "HUD:radar_gangy");
    TextDrawFont(YellowButtonPhone[1], 4);
    TextDrawLetterSize(YellowButtonPhone[1], 0.600000, 2.000000);
    TextDrawTextSize(YellowButtonPhone[1], 17.000000, 17.000000);
    TextDrawSetOutline(YellowButtonPhone[1], true);
    TextDrawSetShadow(YellowButtonPhone[1], false);
    TextDrawAlignment(YellowButtonPhone[1], true);
    TextDrawColor(YellowButtonPhone[1], -1);
    TextDrawBackgroundColor(YellowButtonPhone[1], 255);
    TextDrawBoxColor(YellowButtonPhone[1], 50);
    TextDrawUseBox(YellowButtonPhone[1], true);
    TextDrawSetProportional(YellowButtonPhone[1], true);
    TextDrawSetSelectable(YellowButtonPhone[1], true);

    YellowButtonPhone[2] = TextDrawCreate(573.500000, 384.000000, "Yellow");
    TextDrawFont(YellowButtonPhone[2], true);
    TextDrawLetterSize(YellowButtonPhone[2], 0.162498, 1.049998);
    TextDrawTextSize(YellowButtonPhone[2], 400.000000, 122.000000);
    TextDrawSetOutline(YellowButtonPhone[2], false);
    TextDrawSetShadow(YellowButtonPhone[2], false);
    TextDrawAlignment(YellowButtonPhone[2], 2);
    TextDrawColor(YellowButtonPhone[2], -1);
    TextDrawBackgroundColor(YellowButtonPhone[2], 255);
    TextDrawBoxColor(YellowButtonPhone[2], 50);
    TextDrawUseBox(YellowButtonPhone[2], false);
    TextDrawSetProportional(YellowButtonPhone[2], true);
    TextDrawSetSelectable(YellowButtonPhone[2], false);

    PhoneMainMenuClock = TextDrawCreate(538.000000, 208.000000, "10:45");
    TextDrawFont(PhoneMainMenuClock, true);
    TextDrawLetterSize(PhoneMainMenuClock, 0.162498, 1.049998);
    TextDrawTextSize(PhoneMainMenuClock, 400.000000, 122.000000);
    TextDrawSetOutline(PhoneMainMenuClock, false);
    TextDrawSetShadow(PhoneMainMenuClock, false);
    TextDrawAlignment(PhoneMainMenuClock, 2);
    TextDrawColor(PhoneMainMenuClock, -1);
    TextDrawBackgroundColor(PhoneMainMenuClock, 255);
    TextDrawBoxColor(PhoneMainMenuClock, 50);
    TextDrawUseBox(PhoneMainMenuClock, false);
    TextDrawSetProportional(PhoneMainMenuClock, true);
    TextDrawSetSelectable(PhoneMainMenuClock, false);

    GreenButtonIncomingPhone = TextDrawCreate(585.000000, 357.000000, "ld_beat:chit");
    TextDrawFont(GreenButtonIncomingPhone, 4);
    TextDrawLetterSize(GreenButtonIncomingPhone, 0.600000, 2.000000);
    TextDrawTextSize(GreenButtonIncomingPhone, 28.500000, 32.500000);
    TextDrawSetOutline(GreenButtonIncomingPhone, true);
    TextDrawSetShadow(GreenButtonIncomingPhone, false);
    TextDrawAlignment(GreenButtonIncomingPhone, true);
    TextDrawColor(GreenButtonIncomingPhone, 9109759);
    TextDrawBackgroundColor(GreenButtonIncomingPhone, 255);
    TextDrawBoxColor(GreenButtonIncomingPhone, 50);
    TextDrawUseBox(GreenButtonIncomingPhone, true);
    TextDrawSetProportional(GreenButtonIncomingPhone, true);
    TextDrawSetSelectable(GreenButtonIncomingPhone, true);

    RedButtonIncomingPhone = TextDrawCreate(536.000000, 357.000000, "ld_beat:chit");
    TextDrawFont(RedButtonIncomingPhone, 4);
    TextDrawLetterSize(RedButtonIncomingPhone, 0.600000, 2.000000);
    TextDrawTextSize(RedButtonIncomingPhone, 28.500000, 32.500000);
    TextDrawSetOutline(RedButtonIncomingPhone, true);
    TextDrawSetShadow(RedButtonIncomingPhone, false);
    TextDrawAlignment(RedButtonIncomingPhone, true);
    TextDrawColor(RedButtonIncomingPhone, -1962934017);
    TextDrawBackgroundColor(RedButtonIncomingPhone, 255);
    TextDrawBoxColor(RedButtonIncomingPhone, 50);
    TextDrawUseBox(RedButtonIncomingPhone, true);
    TextDrawSetProportional(RedButtonIncomingPhone, true);
    TextDrawSetSelectable(RedButtonIncomingPhone, true);

    RedButtonOutcomingPhone = TextDrawCreate(560.000000, 357.000000, "ld_beat:chit");
    TextDrawFont(RedButtonOutcomingPhone, 4);
    TextDrawLetterSize(RedButtonOutcomingPhone, 0.600000, 2.000000);
    TextDrawTextSize(RedButtonOutcomingPhone, 28.500000, 32.500000);
    TextDrawSetOutline(RedButtonOutcomingPhone, true);
    TextDrawSetShadow(RedButtonOutcomingPhone, false);
    TextDrawAlignment(RedButtonOutcomingPhone, true);
    TextDrawColor(RedButtonOutcomingPhone, -1962934017);
    TextDrawBackgroundColor(RedButtonOutcomingPhone, 255);
    TextDrawBoxColor(RedButtonOutcomingPhone, 50);
    TextDrawUseBox(RedButtonOutcomingPhone, true);
    TextDrawSetProportional(RedButtonOutcomingPhone, true);
    TextDrawSetSelectable(RedButtonOutcomingPhone, true);

    //banking
    BankingTD[0] = TextDrawCreate(574.000000, 248.000000, "_");
    TextDrawFont(BankingTD[0], false);
    TextDrawLetterSize(BankingTD[0], 0.608331, 14.850018);
    TextDrawTextSize(BankingTD[0], 298.500000, 90.000000);
    TextDrawSetOutline(BankingTD[0], true);
    TextDrawSetShadow(BankingTD[0], false);
    TextDrawAlignment(BankingTD[0], 2);
    TextDrawColor(BankingTD[0], -1);
    TextDrawBackgroundColor(BankingTD[0], 255);
    TextDrawBoxColor(BankingTD[0], 255);
    TextDrawUseBox(BankingTD[0], true);
    TextDrawSetProportional(BankingTD[0], true);
    TextDrawSetSelectable(BankingTD[0], false);

    BankingTD[1] = TextDrawCreate(553.000000, 250.000000, "M-Banking");
    TextDrawFont(BankingTD[1], true);
    TextDrawLetterSize(BankingTD[1], 0.179166, 0.950000);
    TextDrawTextSize(BankingTD[1], 400.000000, 94.000000);
    TextDrawSetOutline(BankingTD[1], false);
    TextDrawSetShadow(BankingTD[1], false);
    TextDrawAlignment(BankingTD[1], 2);
    TextDrawColor(BankingTD[1], -1);
    TextDrawBackgroundColor(BankingTD[1], 255);
    TextDrawBoxColor(BankingTD[1], 50);
    TextDrawUseBox(BankingTD[1], false);
    TextDrawSetProportional(BankingTD[1], true);
    TextDrawSetSelectable(BankingTD[1], false);

    BankingTD[2] = TextDrawCreate(597.000000, 271.000000, "Saldo");
    TextDrawFont(BankingTD[2], true);
    TextDrawLetterSize(BankingTD[2], 0.179166, 0.950000);
    TextDrawTextSize(BankingTD[2], 400.000000, 94.000000);
    TextDrawSetOutline(BankingTD[2], false);
    TextDrawSetShadow(BankingTD[2], false);
    TextDrawAlignment(BankingTD[2], 2);
    TextDrawColor(BankingTD[2], -1);
    TextDrawBackgroundColor(BankingTD[2], 255);
    TextDrawBoxColor(BankingTD[2], 50);
    TextDrawUseBox(BankingTD[2], false);
    TextDrawSetProportional(BankingTD[2], true);
    TextDrawSetSelectable(BankingTD[2], false);

    BankingTD[3] = TextDrawCreate(574.000000, 264.000000, "_");
    TextDrawFont(BankingTD[3], false);
    TextDrawLetterSize(BankingTD[3], 0.608331, 0.200006);
    TextDrawTextSize(BankingTD[3], 298.500000, 90.000000);
    TextDrawSetOutline(BankingTD[3], true);
    TextDrawSetShadow(BankingTD[3], false);
    TextDrawAlignment(BankingTD[3], 2);
    TextDrawColor(BankingTD[3], -1);
    TextDrawBackgroundColor(BankingTD[3], 255);
    TextDrawBoxColor(BankingTD[3], 1296911871);
    TextDrawUseBox(BankingTD[3], true);
    TextDrawSetProportional(BankingTD[3], true);
    TextDrawSetSelectable(BankingTD[3], false);

    BankingTD[4] = TextDrawCreate(574.000000, 283.000000, "_");
    TextDrawFont(BankingTD[4], false);
    TextDrawLetterSize(BankingTD[4], 0.608331, 1.150007);
    TextDrawTextSize(BankingTD[4], 298.500000, 64.000000);
    TextDrawSetOutline(BankingTD[4], true);
    TextDrawSetShadow(BankingTD[4], false);
    TextDrawAlignment(BankingTD[4], 2);
    TextDrawColor(BankingTD[4], -1);
    TextDrawBackgroundColor(BankingTD[4], 255);
    TextDrawBoxColor(BankingTD[4], 1296911871);
    TextDrawUseBox(BankingTD[4], true);
    TextDrawSetProportional(BankingTD[4], true);
    TextDrawSetSelectable(BankingTD[4], false);

    BankingTD[5] = TextDrawCreate(561.000000, 364.000000, "Transfer");
    TextDrawFont(BankingTD[5], true);
    TextDrawLetterSize(BankingTD[5], 0.187166, 1.149999);
    TextDrawTextSize(BankingTD[5], 588.000000, 10.000000);
    TextDrawSetOutline(BankingTD[5], false);
    TextDrawSetShadow(BankingTD[5], false);
    TextDrawAlignment(BankingTD[5], true);
    TextDrawColor(BankingTD[5], -1);
    TextDrawBackgroundColor(BankingTD[5], 255);
    TextDrawBoxColor(BankingTD[5], 9109704);
    TextDrawUseBox(BankingTD[5], true);
    TextDrawSetProportional(BankingTD[5], true);
    TextDrawSetSelectable(BankingTD[5], true);

    BankingTD[6] = TextDrawCreate(574.000000, 225.000000, "Fleeca Bank");
    TextDrawFont(BankingTD[6], true);
    TextDrawLetterSize(BankingTD[6], 0.220833, 1.250000);
    TextDrawTextSize(BankingTD[6], 400.000000, 97.000000);
    TextDrawSetOutline(BankingTD[6], false);
    TextDrawSetShadow(BankingTD[6], false);
    TextDrawAlignment(BankingTD[6], 2);
    TextDrawColor(BankingTD[6], -1);
    TextDrawBackgroundColor(BankingTD[6], 255);
    TextDrawBoxColor(BankingTD[6], 50);
    TextDrawUseBox(BankingTD[6], false);
    TextDrawSetProportional(BankingTD[6], true);
    TextDrawSetSelectable(BankingTD[6], false);

    BankingTD[7] = TextDrawCreate(574.000000, 310.000000, "_");
    TextDrawFont(BankingTD[7], false);
    TextDrawLetterSize(BankingTD[7], 0.608331, 1.150007);
    TextDrawTextSize(BankingTD[7], 298.500000, 64.000000);
    TextDrawSetOutline(BankingTD[7], true);
    TextDrawSetShadow(BankingTD[7], false);
    TextDrawAlignment(BankingTD[7], 2);
    TextDrawColor(BankingTD[7], -1);
    TextDrawBackgroundColor(BankingTD[7], 255);
    TextDrawBoxColor(BankingTD[7], 1296911871);
    TextDrawUseBox(BankingTD[7], true);
    TextDrawSetProportional(BankingTD[7], true);
    TextDrawSetSelectable(BankingTD[7], false);

    BankingTD[8] = TextDrawCreate(597.000000, 298.000000, "Nama");
    TextDrawFont(BankingTD[8], true);
    TextDrawLetterSize(BankingTD[8], 0.179166, 0.950000);
    TextDrawTextSize(BankingTD[8], 400.000000, 94.000000);
    TextDrawSetOutline(BankingTD[8], false);
    TextDrawSetShadow(BankingTD[8], false);
    TextDrawAlignment(BankingTD[8], 2);
    TextDrawColor(BankingTD[8], -1);
    TextDrawBackgroundColor(BankingTD[8], 255);
    TextDrawBoxColor(BankingTD[8], 50);
    TextDrawUseBox(BankingTD[8], false);
    TextDrawSetProportional(BankingTD[8], true);
    TextDrawSetSelectable(BankingTD[8], false);

    BankingTD[9] = TextDrawCreate(593.000000, 326.000000, "No. Rek");
    TextDrawFont(BankingTD[9], true);
    TextDrawLetterSize(BankingTD[9], 0.179166, 0.950000);
    TextDrawTextSize(BankingTD[9], 400.000000, 94.000000);
    TextDrawSetOutline(BankingTD[9], false);
    TextDrawSetShadow(BankingTD[9], false);
    TextDrawAlignment(BankingTD[9], 2);
    TextDrawColor(BankingTD[9], -1);
    TextDrawBackgroundColor(BankingTD[9], 255);
    TextDrawBoxColor(BankingTD[9], 50);
    TextDrawUseBox(BankingTD[9], false);
    TextDrawSetProportional(BankingTD[9], true);
    TextDrawSetSelectable(BankingTD[9], false);

    BankingTD[10] = TextDrawCreate(574.000000, 338.000000, "_");
    TextDrawFont(BankingTD[10], false);
    TextDrawLetterSize(BankingTD[10], 0.608331, 1.150007);
    TextDrawTextSize(BankingTD[10], 298.500000, 64.000000);
    TextDrawSetOutline(BankingTD[10], true);
    TextDrawSetShadow(BankingTD[10], false);
    TextDrawAlignment(BankingTD[10], 2);
    TextDrawColor(BankingTD[10], -1);
    TextDrawBackgroundColor(BankingTD[10], 255);
    TextDrawBoxColor(BankingTD[10], 1296911871);
    TextDrawUseBox(BankingTD[10], true);
    TextDrawSetProportional(BankingTD[10], true);
    TextDrawSetSelectable(BankingTD[10], false);
}

CreatePhoneAppStoreTD()
{
    AppStoreTD[0] = TextDrawCreate(574.000000, 230.000000, "_");
    TextDrawFont(AppStoreTD[0], false);
    TextDrawLetterSize(AppStoreTD[0], 0.608331, 2.300006);
    TextDrawTextSize(AppStoreTD[0], 298.500000, 98.000000);
    TextDrawSetOutline(AppStoreTD[0], true);
    TextDrawSetShadow(AppStoreTD[0], false);
    TextDrawAlignment(AppStoreTD[0], 2);
    TextDrawColor(AppStoreTD[0], -1);
    TextDrawBackgroundColor(AppStoreTD[0], 255);
    TextDrawBoxColor(AppStoreTD[0], -1094795521);
    TextDrawUseBox(AppStoreTD[0], true);
    TextDrawSetProportional(AppStoreTD[0], true);
    TextDrawSetSelectable(AppStoreTD[0], false);

    AppStoreTD[1] = TextDrawCreate(541.000000, 230.000000, "_");
    TextDrawFont(AppStoreTD[1], false);
    TextDrawLetterSize(AppStoreTD[1], 0.608331, 2.300006);
    TextDrawTextSize(AppStoreTD[1], 298.500000, 22.500000);
    TextDrawSetOutline(AppStoreTD[1], true);
    TextDrawSetShadow(AppStoreTD[1], false);
    TextDrawAlignment(AppStoreTD[1], 2);
    TextDrawColor(AppStoreTD[1], -1);
    TextDrawBackgroundColor(AppStoreTD[1], 255);
    TextDrawBoxColor(AppStoreTD[1], 16711935);
    TextDrawUseBox(AppStoreTD[1], true);
    TextDrawSetProportional(AppStoreTD[1], true);
    TextDrawSetSelectable(AppStoreTD[1], false);

    AppStoreTD[2] = TextDrawCreate(574.000000, 256.000000, "_");
    TextDrawFont(AppStoreTD[2], false);
    TextDrawLetterSize(AppStoreTD[2], 0.608331, 2.300006);
    TextDrawTextSize(AppStoreTD[2], 298.500000, 98.000000);
    TextDrawSetOutline(AppStoreTD[2], true);
    TextDrawSetShadow(AppStoreTD[2], false);
    TextDrawAlignment(AppStoreTD[2], 2);
    TextDrawColor(AppStoreTD[2], -1);
    TextDrawBackgroundColor(AppStoreTD[2], 255);
    TextDrawBoxColor(AppStoreTD[2], -1094795521);
    TextDrawUseBox(AppStoreTD[2], true);
    TextDrawSetProportional(AppStoreTD[2], true);
    TextDrawSetSelectable(AppStoreTD[2], false);

    AppStoreTD[3] = TextDrawCreate(541.000000, 256.000000, "_");
    TextDrawFont(AppStoreTD[3], false);
    TextDrawLetterSize(AppStoreTD[3], 0.608331, 2.300006);
    TextDrawTextSize(AppStoreTD[3], 298.500000, 22.500000);
    TextDrawSetOutline(AppStoreTD[3], true);
    TextDrawSetShadow(AppStoreTD[3], false);
    TextDrawAlignment(AppStoreTD[3], 2);
    TextDrawColor(AppStoreTD[3], -1);
    TextDrawBackgroundColor(AppStoreTD[3], 255);
    TextDrawBoxColor(AppStoreTD[3], 255);
    TextDrawUseBox(AppStoreTD[3], true);
    TextDrawSetProportional(AppStoreTD[3], true);
    TextDrawSetSelectable(AppStoreTD[3], false);

    AppStoreTD[4] = TextDrawCreate(574.000000, 282.399993, "_");
    TextDrawFont(AppStoreTD[4], false);
    TextDrawLetterSize(AppStoreTD[4], 0.608331, 2.300006);
    TextDrawTextSize(AppStoreTD[4], 298.500000, 98.000000);
    TextDrawSetOutline(AppStoreTD[4], true);
    TextDrawSetShadow(AppStoreTD[4], false);
    TextDrawAlignment(AppStoreTD[4], 2);
    TextDrawColor(AppStoreTD[4], -1);
    TextDrawBackgroundColor(AppStoreTD[4], 255);
    TextDrawBoxColor(AppStoreTD[4], -1094795521);
    TextDrawUseBox(AppStoreTD[4], true);
    TextDrawSetProportional(AppStoreTD[4], true);
    TextDrawSetSelectable(AppStoreTD[4], false);

    AppStoreTD[5] = TextDrawCreate(541.000000, 282.399993, "_");
    TextDrawFont(AppStoreTD[5], false);
    TextDrawLetterSize(AppStoreTD[5], 0.608331, 2.300006);
    TextDrawTextSize(AppStoreTD[5], 298.500000, 22.500000);
    TextDrawSetOutline(AppStoreTD[5], true);
    TextDrawSetShadow(AppStoreTD[5], false);
    TextDrawAlignment(AppStoreTD[5], 2);
    TextDrawColor(AppStoreTD[5], -1);
    TextDrawBackgroundColor(AppStoreTD[5], 255);
    TextDrawBoxColor(AppStoreTD[5], 11333375);
    TextDrawUseBox(AppStoreTD[5], true);
    TextDrawSetProportional(AppStoreTD[5], true);
    TextDrawSetSelectable(AppStoreTD[5], false);

    AppStoreTD[6] = TextDrawCreate(574.000000, 308.500000, "_");
    TextDrawFont(AppStoreTD[6], false);
    TextDrawLetterSize(AppStoreTD[6], 0.608331, 2.300006);
    TextDrawTextSize(AppStoreTD[6], 298.500000, 98.000000);
    TextDrawSetOutline(AppStoreTD[6], true);
    TextDrawSetShadow(AppStoreTD[6], false);
    TextDrawAlignment(AppStoreTD[6], 2);
    TextDrawColor(AppStoreTD[6], -1);
    TextDrawBackgroundColor(AppStoreTD[6], 255);
    TextDrawBoxColor(AppStoreTD[6], -1094795521);
    TextDrawUseBox(AppStoreTD[6], true);
    TextDrawSetProportional(AppStoreTD[6], true);
    TextDrawSetSelectable(AppStoreTD[6], false);

    AppStoreTD[7] = TextDrawCreate(541.000000, 308.500000, "_");
    TextDrawFont(AppStoreTD[7], false);
    TextDrawLetterSize(AppStoreTD[7], 0.608331, 2.300006);
    TextDrawTextSize(AppStoreTD[7], 298.500000, 22.500000);
    TextDrawSetOutline(AppStoreTD[7], true);
    TextDrawSetShadow(AppStoreTD[7], false);
    TextDrawAlignment(AppStoreTD[7], 2);
    TextDrawColor(AppStoreTD[7], -1);
    TextDrawBackgroundColor(AppStoreTD[7], 255);
    TextDrawBoxColor(AppStoreTD[7], -1);
    TextDrawUseBox(AppStoreTD[7], true);
    TextDrawSetProportional(AppStoreTD[7], true);
    TextDrawSetSelectable(AppStoreTD[7], false);

    AppStoreTD[8] = TextDrawCreate(574.000000, 334.500000, "_");
    TextDrawFont(AppStoreTD[8], false);
    TextDrawLetterSize(AppStoreTD[8], 0.608331, 2.300006);
    TextDrawTextSize(AppStoreTD[8], 298.500000, 98.000000);
    TextDrawSetOutline(AppStoreTD[8], true);
    TextDrawSetShadow(AppStoreTD[8], false);
    TextDrawAlignment(AppStoreTD[8], 2);
    TextDrawColor(AppStoreTD[8], -1);
    TextDrawBackgroundColor(AppStoreTD[8], 255);
    TextDrawBoxColor(AppStoreTD[8], -1094795521);
    TextDrawUseBox(AppStoreTD[8], true);
    TextDrawSetProportional(AppStoreTD[8], true);
    TextDrawSetSelectable(AppStoreTD[8], false);

    AppStoreTD[9] = TextDrawCreate(541.000000, 334.500000, "_");
    TextDrawFont(AppStoreTD[9], false);
    TextDrawLetterSize(AppStoreTD[9], 0.608331, 2.300006);
    TextDrawTextSize(AppStoreTD[9], 298.500000, 22.500000);
    TextDrawSetOutline(AppStoreTD[9], true);
    TextDrawSetShadow(AppStoreTD[9], false);
    TextDrawAlignment(AppStoreTD[9], 2);
    TextDrawColor(AppStoreTD[9], -1);
    TextDrawBackgroundColor(AppStoreTD[9], 255);
    TextDrawBoxColor(AppStoreTD[9], -2686721);
    TextDrawUseBox(AppStoreTD[9], true);
    TextDrawSetProportional(AppStoreTD[9], true);
    TextDrawSetSelectable(AppStoreTD[9], false);

    AppStoreTD[10] = TextDrawCreate(533.000000, 232.000000, "ld_chat:goodcha");
    TextDrawFont(AppStoreTD[10], 4);
    TextDrawLetterSize(AppStoreTD[10], 0.600000, 2.000000);
    TextDrawTextSize(AppStoreTD[10], 17.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[10], true);
    TextDrawSetShadow(AppStoreTD[10], false);
    TextDrawAlignment(AppStoreTD[10], true);
    TextDrawColor(AppStoreTD[10], -1);
    TextDrawBackgroundColor(AppStoreTD[10], 255);
    TextDrawBoxColor(AppStoreTD[10], 50);
    TextDrawUseBox(AppStoreTD[10], true);
    TextDrawSetProportional(AppStoreTD[10], true);
    TextDrawSetSelectable(AppStoreTD[10], false);

    AppStoreTD[11] = TextDrawCreate(556.000000, 229.000000, "WhatsApp");
    TextDrawFont(AppStoreTD[11], true);
    TextDrawLetterSize(AppStoreTD[11], 0.137500, 0.900000);
    TextDrawTextSize(AppStoreTD[11], 605.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[11], false);
    TextDrawSetShadow(AppStoreTD[11], false);
    TextDrawAlignment(AppStoreTD[11], true);
    TextDrawColor(AppStoreTD[11], 255);
    TextDrawBackgroundColor(AppStoreTD[11], 255);
    TextDrawBoxColor(AppStoreTD[11], 50);
    TextDrawUseBox(AppStoreTD[11], false);
    TextDrawSetProportional(AppStoreTD[11], true);
    TextDrawSetSelectable(AppStoreTD[11], false);

    AppStoreTD[12] = TextDrawCreate(556.000000, 237.000000, "Sederhana. Reliabel. Privat");
    TextDrawFont(AppStoreTD[12], true);
    TextDrawLetterSize(AppStoreTD[12], 0.108333, 0.700000);
    TextDrawTextSize(AppStoreTD[12], 590.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[12], false);
    TextDrawSetShadow(AppStoreTD[12], false);
    TextDrawAlignment(AppStoreTD[12], true);
    TextDrawColor(AppStoreTD[12], 1296911871);
    TextDrawBackgroundColor(AppStoreTD[12], 255);
    TextDrawBoxColor(AppStoreTD[12], 50);
    TextDrawUseBox(AppStoreTD[12], false);
    TextDrawSetProportional(AppStoreTD[12], true);
    TextDrawSetSelectable(AppStoreTD[12], false);

    InstallWAButtonPhone = TextDrawCreate(594.000000, 236.500000, "PASANG");
    TextDrawFont(InstallWAButtonPhone, true);
    TextDrawLetterSize(InstallWAButtonPhone, 0.145833, 0.750000);
    TextDrawTextSize(InstallWAButtonPhone, 616.000000, 10.000000);
    TextDrawSetOutline(InstallWAButtonPhone, false);
    TextDrawSetShadow(InstallWAButtonPhone, false);
    TextDrawAlignment(InstallWAButtonPhone, true);
    TextDrawColor(InstallWAButtonPhone, -1);
    TextDrawBackgroundColor(InstallWAButtonPhone, 255);
    TextDrawBoxColor(InstallWAButtonPhone, 1687547391);
    TextDrawUseBox(InstallWAButtonPhone, true);
    TextDrawSetProportional(InstallWAButtonPhone, true);
    TextDrawSetSelectable(InstallWAButtonPhone, true);

    AppStoreTD[13] = TextDrawCreate(533.000000, 258.000000, "HUD:radar_datedisco");
    TextDrawFont(AppStoreTD[13], 4);
    TextDrawLetterSize(AppStoreTD[13], 0.600000, 2.000000);
    TextDrawTextSize(AppStoreTD[13], 17.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[13], true);
    TextDrawSetShadow(AppStoreTD[13], false);
    TextDrawAlignment(AppStoreTD[13], true);
    TextDrawColor(AppStoreTD[13], 16711935);
    TextDrawBackgroundColor(AppStoreTD[13], 255);
    TextDrawBoxColor(AppStoreTD[13], 50);
    TextDrawUseBox(AppStoreTD[13], true);
    TextDrawSetProportional(AppStoreTD[13], true);
    TextDrawSetSelectable(AppStoreTD[13], false);

    AppStoreTD[14] = TextDrawCreate(556.000000, 255.000000, "Spotify");
    TextDrawFont(AppStoreTD[14], true);
    TextDrawLetterSize(AppStoreTD[14], 0.137500, 0.900000);
    TextDrawTextSize(AppStoreTD[14], 605.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[14], false);
    TextDrawSetShadow(AppStoreTD[14], false);
    TextDrawAlignment(AppStoreTD[14], true);
    TextDrawColor(AppStoreTD[14], 255);
    TextDrawBackgroundColor(AppStoreTD[14], 255);
    TextDrawBoxColor(AppStoreTD[14], 50);
    TextDrawUseBox(AppStoreTD[14], false);
    TextDrawSetProportional(AppStoreTD[14], true);
    TextDrawSetSelectable(AppStoreTD[14], false);

    AppStoreTD[15] = TextDrawCreate(556.000000, 263.000000, "Dengarkan playlist & musik");
    TextDrawFont(AppStoreTD[15], true);
    TextDrawLetterSize(AppStoreTD[15], 0.108333, 0.700000);
    TextDrawTextSize(AppStoreTD[15], 590.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[15], false);
    TextDrawSetShadow(AppStoreTD[15], false);
    TextDrawAlignment(AppStoreTD[15], true);
    TextDrawColor(AppStoreTD[15], 1296911871);
    TextDrawBackgroundColor(AppStoreTD[15], 255);
    TextDrawBoxColor(AppStoreTD[15], 50);
    TextDrawUseBox(AppStoreTD[15], false);
    TextDrawSetProportional(AppStoreTD[15], true);
    TextDrawSetSelectable(AppStoreTD[15], false);

    InstallSpotifyButtonPhone = TextDrawCreate(594.000000, 262.500000, "PASANG");
    TextDrawFont(InstallSpotifyButtonPhone, true);
    TextDrawLetterSize(InstallSpotifyButtonPhone, 0.145833, 0.750000);
    TextDrawTextSize(InstallSpotifyButtonPhone, 616.000000, 10.000000);
    TextDrawSetOutline(InstallSpotifyButtonPhone, false);
    TextDrawSetShadow(InstallSpotifyButtonPhone, false);
    TextDrawAlignment(InstallSpotifyButtonPhone, true);
    TextDrawColor(InstallSpotifyButtonPhone, -1);
    TextDrawBackgroundColor(InstallSpotifyButtonPhone, 255);
    TextDrawBoxColor(InstallSpotifyButtonPhone, 1687547391);
    TextDrawUseBox(InstallSpotifyButtonPhone, true);
    TextDrawSetProportional(InstallSpotifyButtonPhone, true);
    TextDrawSetSelectable(InstallSpotifyButtonPhone, true);

    AppStoreTD[16] = TextDrawCreate(533.000000, 282.000000, "ld_grav:beea");
    TextDrawFont(AppStoreTD[16], 4);
    TextDrawLetterSize(AppStoreTD[16], 0.600000, 2.000000);
    TextDrawTextSize(AppStoreTD[16], 17.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[16], true);
    TextDrawSetShadow(AppStoreTD[16], false);
    TextDrawAlignment(AppStoreTD[16], true);
    TextDrawColor(AppStoreTD[16], -1);
    TextDrawBackgroundColor(AppStoreTD[16], 255);
    TextDrawBoxColor(AppStoreTD[16], 50);
    TextDrawUseBox(AppStoreTD[16], true);
    TextDrawSetProportional(AppStoreTD[16], true);
    TextDrawSetSelectable(AppStoreTD[16], false);

    AppStoreTD[17] = TextDrawCreate(556.000000, 281.000000, "Twitter");
    TextDrawFont(AppStoreTD[17], true);
    TextDrawLetterSize(AppStoreTD[17], 0.137500, 0.900000);
    TextDrawTextSize(AppStoreTD[17], 605.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[17], false);
    TextDrawSetShadow(AppStoreTD[17], false);
    TextDrawAlignment(AppStoreTD[17], true);
    TextDrawColor(AppStoreTD[17], 255);
    TextDrawBackgroundColor(AppStoreTD[17], 255);
    TextDrawBoxColor(AppStoreTD[17], 50);
    TextDrawUseBox(AppStoreTD[17], false);
    TextDrawSetProportional(AppStoreTD[17], true);
    TextDrawSetSelectable(AppStoreTD[17], false);

    AppStoreTD[18] = TextDrawCreate(556.000000, 289.000000, "Galau, alay, pansos, caper");
    TextDrawFont(AppStoreTD[18], true);
    TextDrawLetterSize(AppStoreTD[18], 0.108333, 0.700000);
    TextDrawTextSize(AppStoreTD[18], 590.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[18], false);
    TextDrawSetShadow(AppStoreTD[18], false);
    TextDrawAlignment(AppStoreTD[18], true);
    TextDrawColor(AppStoreTD[18], 1296911871);
    TextDrawBackgroundColor(AppStoreTD[18], 255);
    TextDrawBoxColor(AppStoreTD[18], 50);
    TextDrawUseBox(AppStoreTD[18], false);
    TextDrawSetProportional(AppStoreTD[18], true);
    TextDrawSetSelectable(AppStoreTD[18], false);

    InstallTwitterButtonPhone = TextDrawCreate(594.000000, 288.500000, "PASANG");
    TextDrawFont(InstallTwitterButtonPhone, true);
    TextDrawLetterSize(InstallTwitterButtonPhone, 0.145833, 0.750000);
    TextDrawTextSize(InstallTwitterButtonPhone, 616.000000, 10.000000);
    TextDrawSetOutline(InstallTwitterButtonPhone, false);
    TextDrawSetShadow(InstallTwitterButtonPhone, false);
    TextDrawAlignment(InstallTwitterButtonPhone, true);
    TextDrawColor(InstallTwitterButtonPhone, -1);
    TextDrawBackgroundColor(InstallTwitterButtonPhone, 255);
    TextDrawBoxColor(InstallTwitterButtonPhone, 1687547391);
    TextDrawUseBox(InstallTwitterButtonPhone, true);
    TextDrawSetProportional(InstallTwitterButtonPhone, true);
    TextDrawSetSelectable(InstallTwitterButtonPhone, true);

    AppStoreTD[19] = TextDrawCreate(533.000000, 310.000000, "HUD:radar_triadscasino");
    TextDrawFont(AppStoreTD[19], 4);
    TextDrawLetterSize(AppStoreTD[19], 0.600000, 2.000000);
    TextDrawTextSize(AppStoreTD[19], 17.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[19], true);
    TextDrawSetShadow(AppStoreTD[19], false);
    TextDrawAlignment(AppStoreTD[19], true);
    TextDrawColor(AppStoreTD[19], -1094795521);
    TextDrawBackgroundColor(AppStoreTD[19], 255);
    TextDrawBoxColor(AppStoreTD[19], 50);
    TextDrawUseBox(AppStoreTD[19], true);
    TextDrawSetProportional(AppStoreTD[19], true);
    TextDrawSetSelectable(AppStoreTD[19], false);

    AppStoreTD[20] = TextDrawCreate(556.000000, 307.000000, "Uber");
    TextDrawFont(AppStoreTD[20], 1);
    TextDrawLetterSize(AppStoreTD[20], 0.137500, 0.900000);
    TextDrawTextSize(AppStoreTD[20], 605.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[20], 0);
    TextDrawSetShadow(AppStoreTD[20], 0);
    TextDrawAlignment(AppStoreTD[20], 1);
    TextDrawColor(AppStoreTD[20], 255);
    TextDrawBackgroundColor(AppStoreTD[20], 255);
    TextDrawBoxColor(AppStoreTD[20], 50);
    TextDrawUseBox(AppStoreTD[20], 0);
    TextDrawSetProportional(AppStoreTD[20], 1);
    TextDrawSetSelectable(AppStoreTD[20], 0);

    AppStoreTD[21] = TextDrawCreate(556.000000, 315.000000, "For all the places you want to go");
    TextDrawFont(AppStoreTD[21], 1);
    TextDrawLetterSize(AppStoreTD[21], 0.108333, 0.700000);
    TextDrawTextSize(AppStoreTD[21], 590.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[21], 0);
    TextDrawSetShadow(AppStoreTD[21], 0);
    TextDrawAlignment(AppStoreTD[21], 1);
    TextDrawColor(AppStoreTD[21], 1296911871);
    TextDrawBackgroundColor(AppStoreTD[21], 255);
    TextDrawBoxColor(AppStoreTD[21], 50);
    TextDrawUseBox(AppStoreTD[21], 0);
    TextDrawSetProportional(AppStoreTD[21], 1);
    TextDrawSetSelectable(AppStoreTD[21], 0);

    InstallUberButtonPhone = TextDrawCreate(594.000000, 314.500000, "PASANG");
    TextDrawFont(InstallUberButtonPhone, 1);
    TextDrawLetterSize(InstallUberButtonPhone, 0.145833, 0.750000);
    TextDrawTextSize(InstallUberButtonPhone, 616.000000, 10.000000);
    TextDrawSetOutline(InstallUberButtonPhone, 0);
    TextDrawSetShadow(InstallUberButtonPhone, 0);
    TextDrawAlignment(InstallUberButtonPhone, 1);
    TextDrawColor(InstallUberButtonPhone, -1);
    TextDrawBackgroundColor(InstallUberButtonPhone, 255);
    TextDrawBoxColor(InstallUberButtonPhone, 1687547391);
    TextDrawUseBox(InstallUberButtonPhone, 1);
    TextDrawSetProportional(InstallUberButtonPhone, 1);
    TextDrawSetSelectable(InstallUberButtonPhone, 1);

    AppStoreTD[22] = TextDrawCreate(533.000000, 336.000000, "HUD:radar_gangy");
    TextDrawFont(AppStoreTD[22], 4);
    TextDrawLetterSize(AppStoreTD[22], 0.600000, 2.000000);
    TextDrawTextSize(AppStoreTD[22], 17.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[22], 1);
    TextDrawSetShadow(AppStoreTD[22], 0);
    TextDrawAlignment(AppStoreTD[22], 1);
    TextDrawColor(AppStoreTD[22], -1);
    TextDrawBackgroundColor(AppStoreTD[22], 255);
    TextDrawBoxColor(AppStoreTD[22], 50);
    TextDrawUseBox(AppStoreTD[22], 1);
    TextDrawSetProportional(AppStoreTD[22], 1);
    TextDrawSetSelectable(AppStoreTD[22], 0);

    AppStoreTD[23] = TextDrawCreate(556.000000, 333.000000, "Yellow");
    TextDrawFont(AppStoreTD[23], true);
    TextDrawLetterSize(AppStoreTD[23], 0.137500, 0.900000);
    TextDrawTextSize(AppStoreTD[23], 605.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[23], false);
    TextDrawSetShadow(AppStoreTD[23], false);
    TextDrawAlignment(AppStoreTD[23], true);
    TextDrawColor(AppStoreTD[23], 255);
    TextDrawBackgroundColor(AppStoreTD[23], 255);
    TextDrawBoxColor(AppStoreTD[23], 50);
    TextDrawUseBox(AppStoreTD[23], false);
    TextDrawSetProportional(AppStoreTD[23], true);
    TextDrawSetSelectable(AppStoreTD[23], false);

    AppStoreTD[24] = TextDrawCreate(556.000000, 341.000000, "Promosi dan iklan jadi lebih mudah");
    TextDrawFont(AppStoreTD[24], true);
    TextDrawLetterSize(AppStoreTD[24], 0.108333, 0.700000);
    TextDrawTextSize(AppStoreTD[24], 590.000000, 17.000000);
    TextDrawSetOutline(AppStoreTD[24], false);
    TextDrawSetShadow(AppStoreTD[24], false);
    TextDrawAlignment(AppStoreTD[24], true);
    TextDrawColor(AppStoreTD[24], 1296911871);
    TextDrawBackgroundColor(AppStoreTD[24], 255);
    TextDrawBoxColor(AppStoreTD[24], 50);
    TextDrawUseBox(AppStoreTD[24], false);
    TextDrawSetProportional(AppStoreTD[24], true);
    TextDrawSetSelectable(AppStoreTD[24], false);

    InstallYellowButtonPhone = TextDrawCreate(594.000000, 341.500000, "PASANG");
    TextDrawFont(InstallYellowButtonPhone, true);
    TextDrawLetterSize(InstallYellowButtonPhone, 0.145833, 0.750000);
    TextDrawTextSize(InstallYellowButtonPhone, 616.000000, 10.000000);
    TextDrawSetOutline(InstallYellowButtonPhone, false);
    TextDrawSetShadow(InstallYellowButtonPhone, false);
    TextDrawAlignment(InstallYellowButtonPhone, true);
    TextDrawColor(InstallYellowButtonPhone, -1);
    TextDrawBackgroundColor(InstallYellowButtonPhone, 255);
    TextDrawBoxColor(InstallYellowButtonPhone, 1687547391);
    TextDrawUseBox(InstallYellowButtonPhone, true);
    TextDrawSetProportional(InstallYellowButtonPhone, true);
    TextDrawSetSelectable(InstallYellowButtonPhone, true);

    AppStoreTD[25] = TextDrawCreate(546.000000, 215.000000, "Featured App");
    TextDrawFont(AppStoreTD[25], true);
    TextDrawLetterSize(AppStoreTD[25], 0.166666, 1.050000);
    TextDrawTextSize(AppStoreTD[25], 400.000000, 97.000000);
    TextDrawSetOutline(AppStoreTD[25], false);
    TextDrawSetShadow(AppStoreTD[25], false);
    TextDrawAlignment(AppStoreTD[25], 2);
    TextDrawColor(AppStoreTD[25], 255);
    TextDrawBackgroundColor(AppStoreTD[25], 255);
    TextDrawBoxColor(AppStoreTD[25], 50);
    TextDrawUseBox(AppStoreTD[25], false);
    TextDrawSetProportional(AppStoreTD[25], true);
    TextDrawSetSelectable(AppStoreTD[25], false);
}

CreatePhoneContactTD()
{
    ContactTD[0] = TextDrawCreate(574.000000, 230.000000, "_");
    TextDrawFont(ContactTD[0], false);
    TextDrawLetterSize(ContactTD[0], 0.608331, 2.300005);
    TextDrawTextSize(ContactTD[0], 298.500000, 98.000000);
    TextDrawSetOutline(ContactTD[0], true);
    TextDrawSetShadow(ContactTD[0], false);
    TextDrawAlignment(ContactTD[0], 2);
    TextDrawColor(ContactTD[0], -1);
    TextDrawBackgroundColor(ContactTD[0], 255);
    TextDrawBoxColor(ContactTD[0], -1094795521);
    TextDrawUseBox(ContactTD[0], true);
    TextDrawSetProportional(ContactTD[0], true);
    TextDrawSetSelectable(ContactTD[0], false);

    ContactTD[1] = TextDrawCreate(546.000000, 234.000000, "Tambah kontak baru");
    TextDrawFont(ContactTD[1], true);
    TextDrawLetterSize(ContactTD[1], 0.166666, 1.049998);
    TextDrawTextSize(ContactTD[1], 607.000000, 10.000000);
    TextDrawSetOutline(ContactTD[1], false);
    TextDrawSetShadow(ContactTD[1], false);
    TextDrawAlignment(ContactTD[1], true);
    TextDrawColor(ContactTD[1], 255);
    TextDrawBackgroundColor(ContactTD[1], 255);
    TextDrawBoxColor(ContactTD[1], 50);
    TextDrawUseBox(ContactTD[1], false);
    TextDrawSetProportional(ContactTD[1], true);
    TextDrawSetSelectable(ContactTD[1], true);

    ContactTD[2] = TextDrawCreate(574.000000, 256.000000, "_");
    TextDrawFont(ContactTD[2], false);
    TextDrawLetterSize(ContactTD[2], 0.608331, 2.300005);
    TextDrawTextSize(ContactTD[2], 298.500000, 98.000000);
    TextDrawSetOutline(ContactTD[2], true);
    TextDrawSetShadow(ContactTD[2], false);
    TextDrawAlignment(ContactTD[2], 2);
    TextDrawColor(ContactTD[2], -1);
    TextDrawBackgroundColor(ContactTD[2], 255);
    TextDrawBoxColor(ContactTD[2], -1094795521);
    TextDrawUseBox(ContactTD[2], true);
    TextDrawSetProportional(ContactTD[2], true);
    TextDrawSetSelectable(ContactTD[2], false);

    ContactTD[3] = TextDrawCreate(555.000000, 261.000000, "Daftar kontak");
    TextDrawFont(ContactTD[3], true);
    TextDrawLetterSize(ContactTD[3], 0.166666, 1.049998);
    TextDrawTextSize(ContactTD[3], 605.000000, 10.000000);
    TextDrawSetOutline(ContactTD[3], false);
    TextDrawSetShadow(ContactTD[3], false);
    TextDrawAlignment(ContactTD[3], true);
    TextDrawColor(ContactTD[3], 255);
    TextDrawBackgroundColor(ContactTD[3], 255);
    TextDrawBoxColor(ContactTD[3], 50);
    TextDrawUseBox(ContactTD[3], false);
    TextDrawSetProportional(ContactTD[3], true);
    TextDrawSetSelectable(ContactTD[3], true);

    ContactTD[4] = TextDrawCreate(539.000000, 215.000000, "Kontak");
    TextDrawFont(ContactTD[4], true);
    TextDrawLetterSize(ContactTD[4], 0.166666, 1.049999);
    TextDrawTextSize(ContactTD[4], 400.000000, 97.000000);
    TextDrawSetOutline(ContactTD[4], false);
    TextDrawSetShadow(ContactTD[4], false);
    TextDrawAlignment(ContactTD[4], 2);
    TextDrawColor(ContactTD[4], 255);
    TextDrawBackgroundColor(ContactTD[4], 255);
    TextDrawBoxColor(ContactTD[4], 50);
    TextDrawUseBox(ContactTD[4], false);
    TextDrawSetProportional(ContactTD[4], true);
    TextDrawSetSelectable(ContactTD[4], false);
}

CreatePhoneSettingsTD()
{
    SettingsTD[0] = TextDrawCreate(562.000000, 261.000000, "Wallpaper");
    TextDrawFont(SettingsTD[0], true);
    TextDrawLetterSize(SettingsTD[0], 0.166666, 1.049998);
    TextDrawTextSize(SettingsTD[0], 619.000000, 10.000000);
    TextDrawSetOutline(SettingsTD[0], false);
    TextDrawSetShadow(SettingsTD[0], false);
    TextDrawAlignment(SettingsTD[0], true);
    TextDrawColor(SettingsTD[0], 255);
    TextDrawBackgroundColor(SettingsTD[0], 255);
    TextDrawBoxColor(SettingsTD[0], 50);
    TextDrawUseBox(SettingsTD[0], false);
    TextDrawSetProportional(SettingsTD[0], true);
    TextDrawSetSelectable(SettingsTD[0], true);

    SettingsTD[1] = TextDrawCreate(545.000000, 215.000000, "Pengaturan");
    TextDrawFont(SettingsTD[1], true);
    TextDrawLetterSize(SettingsTD[1], 0.166666, 1.049998);
    TextDrawTextSize(SettingsTD[1], 400.000000, 97.000000);
    TextDrawSetOutline(SettingsTD[1], false);
    TextDrawSetShadow(SettingsTD[1], false);
    TextDrawAlignment(SettingsTD[1], 2);
    TextDrawColor(SettingsTD[1], 255);
    TextDrawBackgroundColor(SettingsTD[1], 255);
    TextDrawBoxColor(SettingsTD[1], 50);
    TextDrawUseBox(SettingsTD[1], false);
    TextDrawSetProportional(SettingsTD[1], true);
    TextDrawSetSelectable(SettingsTD[1], false);

    SettingsTD[2] = TextDrawCreate(554.000000, 234.000000, "Tentang ponsel");
    TextDrawFont(SettingsTD[2], true);
    TextDrawLetterSize(SettingsTD[2], 0.166666, 1.049998);
    TextDrawTextSize(SettingsTD[2], 615.000000, 10.000000);
    TextDrawSetOutline(SettingsTD[2], false);
    TextDrawSetShadow(SettingsTD[2], false);
    TextDrawAlignment(SettingsTD[2], true);
    TextDrawColor(SettingsTD[2], 255);
    TextDrawBackgroundColor(SettingsTD[2], 255);
    TextDrawBoxColor(SettingsTD[2], 50);
    TextDrawUseBox(SettingsTD[2], false);
    TextDrawSetProportional(SettingsTD[2], true);
    TextDrawSetSelectable(SettingsTD[2], true);
}

CreatePhoneSpotifyTD()
{
    SpotifyTD[0] = TextDrawCreate(574.000000, 208.000000, "_");
    TextDrawFont(SpotifyTD[0], false);
    TextDrawLetterSize(SpotifyTD[0], 0.608331, 22.300006);
    TextDrawTextSize(SpotifyTD[0], 298.500000, 98.000000);
    TextDrawSetOutline(SpotifyTD[0], true);
    TextDrawSetShadow(SpotifyTD[0], false);
    TextDrawAlignment(SpotifyTD[0], 2);
    TextDrawColor(SpotifyTD[0], -1);
    TextDrawBackgroundColor(SpotifyTD[0], 255);
    TextDrawBoxColor(SpotifyTD[0], 1296911871);
    TextDrawUseBox(SpotifyTD[0], true);
    TextDrawSetProportional(SpotifyTD[0], true);
    TextDrawSetSelectable(SpotifyTD[0], false);

    SpotifyTD[1] = TextDrawCreate(574.000000, 256.000000, "_");
    TextDrawFont(SpotifyTD[1], false);
    TextDrawLetterSize(SpotifyTD[1], 0.608331, 2.300004);
    TextDrawTextSize(SpotifyTD[1], 298.500000, 98.000000);
    TextDrawSetOutline(SpotifyTD[1], true);
    TextDrawSetShadow(SpotifyTD[1], false);
    TextDrawAlignment(SpotifyTD[1], 2);
    TextDrawColor(SpotifyTD[1], -1);
    TextDrawBackgroundColor(SpotifyTD[1], 255);
    TextDrawBoxColor(SpotifyTD[1], 1768516095);
    TextDrawUseBox(SpotifyTD[1], true);
    TextDrawSetProportional(SpotifyTD[1], true);
    TextDrawSetSelectable(SpotifyTD[1], false);

    SpotifyTD[2] = TextDrawCreate(552.000000, 261.000000, "Putar di boombox");
    TextDrawFont(SpotifyTD[2], true);
    TextDrawLetterSize(SpotifyTD[2], 0.166666, 1.049998);
    TextDrawTextSize(SpotifyTD[2], 620.500000, 10.000000);
    TextDrawSetOutline(SpotifyTD[2], false);
    TextDrawSetShadow(SpotifyTD[2], false);
    TextDrawAlignment(SpotifyTD[2], true);
    TextDrawColor(SpotifyTD[2], -1);
    TextDrawBackgroundColor(SpotifyTD[2], 255);
    TextDrawBoxColor(SpotifyTD[2], 50);
    TextDrawUseBox(SpotifyTD[2], false);
    TextDrawSetProportional(SpotifyTD[2], true);
    TextDrawSetSelectable(SpotifyTD[2], true);

    SpotifyTD[3] = TextDrawCreate(574.000000, 230.000000, "_");
    TextDrawFont(SpotifyTD[3], false);
    TextDrawLetterSize(SpotifyTD[3], 0.608331, 2.300004);
    TextDrawTextSize(SpotifyTD[3], 298.500000, 98.000000);
    TextDrawSetOutline(SpotifyTD[3], true);
    TextDrawSetShadow(SpotifyTD[3], false);
    TextDrawAlignment(SpotifyTD[3], 2);
    TextDrawColor(SpotifyTD[3], -1);
    TextDrawBackgroundColor(SpotifyTD[3], 255);
    TextDrawBoxColor(SpotifyTD[3], 1768516095);
    TextDrawUseBox(SpotifyTD[3], true);
    TextDrawSetProportional(SpotifyTD[3], true);
    TextDrawSetSelectable(SpotifyTD[3], false);

    SpotifyTD[4] = TextDrawCreate(588.000000, 282.000000, "Hai, bagaimana hari ini?");
    TextDrawFont(SpotifyTD[4], true);
    TextDrawLetterSize(SpotifyTD[4], 0.166666, 1.049998);
    TextDrawTextSize(SpotifyTD[4], 400.000000, 97.000000);
    TextDrawSetOutline(SpotifyTD[4], false);
    TextDrawSetShadow(SpotifyTD[4], false);
    TextDrawAlignment(SpotifyTD[4], 2);
    TextDrawColor(SpotifyTD[4], -1);
    TextDrawBackgroundColor(SpotifyTD[4], 255);
    TextDrawBoxColor(SpotifyTD[4], 50);
    TextDrawUseBox(SpotifyTD[4], false);
    TextDrawSetProportional(SpotifyTD[4], true);
    TextDrawSetSelectable(SpotifyTD[4], false);

    SpotifyTD[5] = TextDrawCreate(552.000000, 234.000000, "Putar di earphone");
    TextDrawFont(SpotifyTD[5], true);
    TextDrawLetterSize(SpotifyTD[5], 0.166666, 1.049998);
    TextDrawTextSize(SpotifyTD[5], 621.000000, 10.000000);
    TextDrawSetOutline(SpotifyTD[5], false);
    TextDrawSetShadow(SpotifyTD[5], false);
    TextDrawAlignment(SpotifyTD[5], true);
    TextDrawColor(SpotifyTD[5], -1);
    TextDrawBackgroundColor(SpotifyTD[5], 255);
    TextDrawBoxColor(SpotifyTD[5], 50);
    TextDrawUseBox(SpotifyTD[5], false);
    TextDrawSetProportional(SpotifyTD[5], true);
    TextDrawSetSelectable(SpotifyTD[5], true);

    SpotifyTD[6] = TextDrawCreate(551.000000, 313.000000, "Dipilih untukmu");
    TextDrawFont(SpotifyTD[6], true);
    TextDrawLetterSize(SpotifyTD[6], 0.166666, 1.049998);
    TextDrawTextSize(SpotifyTD[6], 400.000000, 97.000000);
    TextDrawSetOutline(SpotifyTD[6], false);
    TextDrawSetShadow(SpotifyTD[6], false);
    TextDrawAlignment(SpotifyTD[6], 2);
    TextDrawColor(SpotifyTD[6], -1);
    TextDrawBackgroundColor(SpotifyTD[6], 255);
    TextDrawBoxColor(SpotifyTD[6], 50);
    TextDrawUseBox(SpotifyTD[6], false);
    TextDrawSetProportional(SpotifyTD[6], true);
    TextDrawSetSelectable(SpotifyTD[6], false);

    SpotifyTD[7] = TextDrawCreate(574.000000, 332.000000, "_");
    TextDrawFont(SpotifyTD[7], false);
    TextDrawLetterSize(SpotifyTD[7], 0.608331, 3.500002);
    TextDrawTextSize(SpotifyTD[7], 298.500000, 84.000000);
    TextDrawSetOutline(SpotifyTD[7], true);
    TextDrawSetShadow(SpotifyTD[7], false);
    TextDrawAlignment(SpotifyTD[7], 2);
    TextDrawColor(SpotifyTD[7], -1);
    TextDrawBackgroundColor(SpotifyTD[7], 255);
    TextDrawBoxColor(SpotifyTD[7], 1768516095);
    TextDrawUseBox(SpotifyTD[7], true);
    TextDrawSetProportional(SpotifyTD[7], true);
    TextDrawSetSelectable(SpotifyTD[7], false);

    SpotifyTD[8] = TextDrawCreate(567.000000, 331.000000, "Album");
    TextDrawFont(SpotifyTD[8], true);
    TextDrawLetterSize(SpotifyTD[8], 0.166666, 1.049998);
    TextDrawTextSize(SpotifyTD[8], 400.000000, 97.000000);
    TextDrawSetOutline(SpotifyTD[8], false);
    TextDrawSetShadow(SpotifyTD[8], false);
    TextDrawAlignment(SpotifyTD[8], 2);
    TextDrawColor(SpotifyTD[8], -1094795521);
    TextDrawBackgroundColor(SpotifyTD[8], 255);
    TextDrawBoxColor(SpotifyTD[8], 50);
    TextDrawUseBox(SpotifyTD[8], false);
    TextDrawSetProportional(SpotifyTD[8], true);
    TextDrawSetSelectable(SpotifyTD[8], false);

    SpotifyTD[9] = TextDrawCreate(587.000000, 339.000000, "Berpisah Lebih Indah");
    TextDrawFont(SpotifyTD[9], true);
    TextDrawLetterSize(SpotifyTD[9], 0.166666, 1.049998);
    TextDrawTextSize(SpotifyTD[9], 400.000000, 97.000000);
    TextDrawSetOutline(SpotifyTD[9], false);
    TextDrawSetShadow(SpotifyTD[9], false);
    TextDrawAlignment(SpotifyTD[9], 2);
    TextDrawColor(SpotifyTD[9], -1);
    TextDrawBackgroundColor(SpotifyTD[9], 255);
    TextDrawBoxColor(SpotifyTD[9], 50);
    TextDrawUseBox(SpotifyTD[9], false);
    TextDrawSetProportional(SpotifyTD[9], true);
    TextDrawSetSelectable(SpotifyTD[9], false);

    SpotifyTD[10] = TextDrawCreate(559.000000, 349.000000, "Dengarkan single terbaru Raissa Ramadhani sekarang!");
    TextDrawFont(SpotifyTD[10], true);
    TextDrawLetterSize(SpotifyTD[10], 0.124999, 0.799997);
    TextDrawTextSize(SpotifyTD[10], 621.000000, 97.000000);
    TextDrawSetOutline(SpotifyTD[10], false);
    TextDrawSetShadow(SpotifyTD[10], false);
    TextDrawAlignment(SpotifyTD[10], true);
    TextDrawColor(SpotifyTD[10], -1094795521);
    TextDrawBackgroundColor(SpotifyTD[10], 255);
    TextDrawBoxColor(SpotifyTD[10], 50);
    TextDrawUseBox(SpotifyTD[10], false);
    TextDrawSetProportional(SpotifyTD[10], true);
    TextDrawSetSelectable(SpotifyTD[10], false);

    SpotifyTD[11] = TextDrawCreate(610.000000, 313.000000, ":");
    TextDrawFont(SpotifyTD[11], true);
    TextDrawLetterSize(SpotifyTD[11], 0.166666, 1.049998);
    TextDrawTextSize(SpotifyTD[11], 400.000000, 97.000000);
    TextDrawSetOutline(SpotifyTD[11], false);
    TextDrawSetShadow(SpotifyTD[11], false);
    TextDrawAlignment(SpotifyTD[11], 2);
    TextDrawColor(SpotifyTD[11], -1);
    TextDrawBackgroundColor(SpotifyTD[11], 255);
    TextDrawBoxColor(SpotifyTD[11], 50);
    TextDrawUseBox(SpotifyTD[11], false);
    TextDrawSetProportional(SpotifyTD[11], true);
    TextDrawSetSelectable(SpotifyTD[11], false);

    SpotifyTD[12] = TextDrawCreate(531.000000, 331.000000, "ld_bum:bum1");
    TextDrawFont(SpotifyTD[12], 4);
    TextDrawLetterSize(SpotifyTD[12], 0.600000, 2.000000);
    TextDrawTextSize(SpotifyTD[12], 27.000000, 34.500000);
    TextDrawSetOutline(SpotifyTD[12], true);
    TextDrawSetShadow(SpotifyTD[12], false);
    TextDrawAlignment(SpotifyTD[12], true);
    TextDrawColor(SpotifyTD[12], -186);
    TextDrawBackgroundColor(SpotifyTD[12], 255);
    TextDrawBoxColor(SpotifyTD[12], 50);
    TextDrawUseBox(SpotifyTD[12], true);
    TextDrawSetProportional(SpotifyTD[12], true);
    TextDrawSetSelectable(SpotifyTD[12], false);

    SpotifyTD[13] = TextDrawCreate(527.000000, 331.000000, "Preview_Model");
    TextDrawFont(SpotifyTD[13], 5);
    TextDrawLetterSize(SpotifyTD[13], 0.600000, 2.000000);
    TextDrawTextSize(SpotifyTD[13], 34.000000, 35.500000);
    TextDrawSetOutline(SpotifyTD[13], false);
    TextDrawSetShadow(SpotifyTD[13], false);
    TextDrawAlignment(SpotifyTD[13], true);
    TextDrawColor(SpotifyTD[13], -1);
    TextDrawBackgroundColor(SpotifyTD[13], false);
    TextDrawBoxColor(SpotifyTD[13], 255);
    TextDrawUseBox(SpotifyTD[13], false);
    TextDrawSetProportional(SpotifyTD[13], true);
    TextDrawSetSelectable(SpotifyTD[13], false);
    TextDrawSetPreviewModel(SpotifyTD[13], 169);
    TextDrawSetPreviewRot(SpotifyTD[13], -10.000000, 0.000000, 2.000000, 0.789999);
    TextDrawSetPreviewVehCol(SpotifyTD[13], 1, true);
}

CreatePhoneIncomingTD(playerid)
{
    ContactNameTD[playerid] = CreatePlayerTextDraw(playerid, 574.000000, 250.000000, "Mang Ucok Penjual Roti");
    PlayerTextDrawFont(playerid, ContactNameTD[playerid], true);
    PlayerTextDrawLetterSize(playerid, ContactNameTD[playerid], 0.220833, 1.250000);
    PlayerTextDrawTextSize(playerid, ContactNameTD[playerid], 400.000000, 90.500000);
    PlayerTextDrawSetOutline(playerid, ContactNameTD[playerid], false);
    PlayerTextDrawSetShadow(playerid, ContactNameTD[playerid], false);
    PlayerTextDrawAlignment(playerid, ContactNameTD[playerid], 2);
    PlayerTextDrawColor(playerid, ContactNameTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, ContactNameTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, ContactNameTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, ContactNameTD[playerid], false);
    PlayerTextDrawSetProportional(playerid, ContactNameTD[playerid], true);
    PlayerTextDrawSetSelectable(playerid, ContactNameTD[playerid], false);

    StatusDialingTD[playerid] = CreatePlayerTextDraw(playerid, 574.000000, 264.000000, "Panggilan Masuk...");
    PlayerTextDrawFont(playerid, StatusDialingTD[playerid], true);
    PlayerTextDrawLetterSize(playerid, StatusDialingTD[playerid], 0.220833, 1.250000);
    PlayerTextDrawTextSize(playerid, StatusDialingTD[playerid], 400.000000, 90.500000);
    PlayerTextDrawSetOutline(playerid, StatusDialingTD[playerid], false);
    PlayerTextDrawSetShadow(playerid, StatusDialingTD[playerid], false);
    PlayerTextDrawAlignment(playerid, StatusDialingTD[playerid], 2);
    PlayerTextDrawColor(playerid, StatusDialingTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, StatusDialingTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, StatusDialingTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, StatusDialingTD[playerid], false);
    PlayerTextDrawSetProportional(playerid, StatusDialingTD[playerid], true);
    PlayerTextDrawSetSelectable(playerid, StatusDialingTD[playerid], false);
}

CreatePhoneBankingTD(playerid)
{
    PlayerBankingTD[playerid][0] = CreatePlayerTextDraw(playerid, 543.000000, 284.000000, "$20.000.000");
    PlayerTextDrawFont(playerid, PlayerBankingTD[playerid][0], true);
    PlayerTextDrawLetterSize(playerid, PlayerBankingTD[playerid][0], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerBankingTD[playerid][0], 605.000000, 94.000000);
    PlayerTextDrawSetOutline(playerid, PlayerBankingTD[playerid][0], false);
    PlayerTextDrawSetShadow(playerid, PlayerBankingTD[playerid][0], false);
    PlayerTextDrawAlignment(playerid, PlayerBankingTD[playerid][0], true);
    PlayerTextDrawColor(playerid, PlayerBankingTD[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerBankingTD[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, PlayerBankingTD[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, PlayerBankingTD[playerid][0], false);
    PlayerTextDrawSetProportional(playerid, PlayerBankingTD[playerid][0], true);
    PlayerTextDrawSetSelectable(playerid, PlayerBankingTD[playerid][0], false);

    PlayerBankingTD[playerid][1] = CreatePlayerTextDraw(playerid, 543.000000, 310.000000, "Mukhlis Sadewa");
    PlayerTextDrawFont(playerid, PlayerBankingTD[playerid][1], true);
    PlayerTextDrawLetterSize(playerid, PlayerBankingTD[playerid][1], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerBankingTD[playerid][1], 619.000000, 94.000000);
    PlayerTextDrawSetOutline(playerid, PlayerBankingTD[playerid][1], false);
    PlayerTextDrawSetShadow(playerid, PlayerBankingTD[playerid][1], false);
    PlayerTextDrawAlignment(playerid, PlayerBankingTD[playerid][1], true);
    PlayerTextDrawColor(playerid, PlayerBankingTD[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerBankingTD[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, PlayerBankingTD[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, PlayerBankingTD[playerid][1], false);
    PlayerTextDrawSetProportional(playerid, PlayerBankingTD[playerid][1], true);
    PlayerTextDrawSetSelectable(playerid, PlayerBankingTD[playerid][1], false);

    PlayerBankingTD[playerid][2] = CreatePlayerTextDraw(playerid, 543.000000, 338.000000, "123456789");
    PlayerTextDrawFont(playerid, PlayerBankingTD[playerid][2], true);
    PlayerTextDrawLetterSize(playerid, PlayerBankingTD[playerid][2], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerBankingTD[playerid][2], 619.000000, 94.000000);
    PlayerTextDrawSetOutline(playerid, PlayerBankingTD[playerid][2], false);
    PlayerTextDrawSetShadow(playerid, PlayerBankingTD[playerid][2], false);
    PlayerTextDrawAlignment(playerid, PlayerBankingTD[playerid][2], true);
    PlayerTextDrawColor(playerid, PlayerBankingTD[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerBankingTD[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, PlayerBankingTD[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, PlayerBankingTD[playerid][2], false);
    PlayerTextDrawSetProportional(playerid, PlayerBankingTD[playerid][2], true);
    PlayerTextDrawSetSelectable(playerid, PlayerBankingTD[playerid][2], false);
}

CreateTwitterLoginTD()
{
    TwitterLoginTD[0] = TextDrawCreate(574.000000, 208.000000, "_");
    TextDrawFont(TwitterLoginTD[0], false);
    TextDrawLetterSize(TwitterLoginTD[0], 0.608331, 22.300006);
    TextDrawTextSize(TwitterLoginTD[0], 298.500000, 98.000000);
    TextDrawSetOutline(TwitterLoginTD[0], true);
    TextDrawSetShadow(TwitterLoginTD[0], false);
    TextDrawAlignment(TwitterLoginTD[0], 2);
    TextDrawColor(TwitterLoginTD[0], -1);
    TextDrawBackgroundColor(TwitterLoginTD[0], 255);
    TextDrawBoxColor(TwitterLoginTD[0], 497152767);
    TextDrawUseBox(TwitterLoginTD[0], true);
    TextDrawSetProportional(TwitterLoginTD[0], true);
    TextDrawSetSelectable(TwitterLoginTD[0], false);

    TwitterLoginTD[1] = TextDrawCreate(574.000000, 256.000000, "_");
    TextDrawFont(TwitterLoginTD[1], false);
    TextDrawLetterSize(TwitterLoginTD[1], 0.608331, 2.300004);
    TextDrawTextSize(TwitterLoginTD[1], 298.500000, 49.000000);
    TextDrawSetOutline(TwitterLoginTD[1], true);
    TextDrawSetShadow(TwitterLoginTD[1], false);
    TextDrawAlignment(TwitterLoginTD[1], 2);
    TextDrawColor(TwitterLoginTD[1], -1);
    TextDrawBackgroundColor(TwitterLoginTD[1], 255);
    TextDrawBoxColor(TwitterLoginTD[1], -1);
    TextDrawUseBox(TwitterLoginTD[1], true);
    TextDrawSetProportional(TwitterLoginTD[1], true);
    TextDrawSetSelectable(TwitterLoginTD[1], false);

    TwitterLoginTD[2] = TextDrawCreate(568.000000, 261.000000, "Login");
    TextDrawFont(TwitterLoginTD[2], true);
    TextDrawLetterSize(TwitterLoginTD[2], 0.166666, 1.049998);
    TextDrawTextSize(TwitterLoginTD[2], 598.000000, 10.000000);
    TextDrawSetOutline(TwitterLoginTD[2], false);
    TextDrawSetShadow(TwitterLoginTD[2], false);
    TextDrawAlignment(TwitterLoginTD[2], true);
    TextDrawColor(TwitterLoginTD[2], 255);
    TextDrawBackgroundColor(TwitterLoginTD[2], 255);
    TextDrawBoxColor(TwitterLoginTD[2], 50);
    TextDrawUseBox(TwitterLoginTD[2], false);
    TextDrawSetProportional(TwitterLoginTD[2], true);
    TextDrawSetSelectable(TwitterLoginTD[2], true);

    TwitterLoginTD[3] = TextDrawCreate(534.000000, 289.000000, "Belum memiliki akun?");
    TextDrawFont(TwitterLoginTD[3], true);
    TextDrawLetterSize(TwitterLoginTD[3], 0.166666, 1.049998);
    TextDrawTextSize(TwitterLoginTD[3], 613.000000, 97.000000);
    TextDrawSetOutline(TwitterLoginTD[3], false);
    TextDrawSetShadow(TwitterLoginTD[3], false);
    TextDrawAlignment(TwitterLoginTD[3], true);
    TextDrawColor(TwitterLoginTD[3], -1);
    TextDrawBackgroundColor(TwitterLoginTD[3], 255);
    TextDrawBoxColor(TwitterLoginTD[3], 50);
    TextDrawUseBox(TwitterLoginTD[3], false);
    TextDrawSetProportional(TwitterLoginTD[3], true);
    TextDrawSetSelectable(TwitterLoginTD[3], false);

    TwitterLoginTD[4] = TextDrawCreate(529.000000, 229.000000, "Hai, selamat datang di Twitter. Silahkan login!");
    TextDrawFont(TwitterLoginTD[4], true);
    TextDrawLetterSize(TwitterLoginTD[4], 0.166666, 1.049998);
    TextDrawTextSize(TwitterLoginTD[4], 613.000000, 97.000000);
    TextDrawSetOutline(TwitterLoginTD[4], false);
    TextDrawSetShadow(TwitterLoginTD[4], false);
    TextDrawAlignment(TwitterLoginTD[4], true);
    TextDrawColor(TwitterLoginTD[4], -1);
    TextDrawBackgroundColor(TwitterLoginTD[4], 255);
    TextDrawBoxColor(TwitterLoginTD[4], 50);
    TextDrawUseBox(TwitterLoginTD[4], false);
    TextDrawSetProportional(TwitterLoginTD[4], true);
    TextDrawSetSelectable(TwitterLoginTD[4], false);

    TwitterLoginTD[5] = TextDrawCreate(596.000000, 289.000000, "Daftar");
    TextDrawFont(TwitterLoginTD[5], true);
    TextDrawLetterSize(TwitterLoginTD[5], 0.166666, 1.049998);
    TextDrawTextSize(TwitterLoginTD[5], 622.000000, 10.000000);
    TextDrawSetOutline(TwitterLoginTD[5], false);
    TextDrawSetShadow(TwitterLoginTD[5], false);
    TextDrawAlignment(TwitterLoginTD[5], true);
    TextDrawColor(TwitterLoginTD[5], 35839);
    TextDrawBackgroundColor(TwitterLoginTD[5], 255);
    TextDrawBoxColor(TwitterLoginTD[5], 50);
    TextDrawUseBox(TwitterLoginTD[5], false);
    TextDrawSetProportional(TwitterLoginTD[5], true);
    TextDrawSetSelectable(TwitterLoginTD[5], true);
}

CreateTwitterMainTD()
{
    TwitterMainTD[0] = TextDrawCreate(574.000000, 256.000000, "_");
    TextDrawFont(TwitterMainTD[0], false);
    TextDrawLetterSize(TwitterMainTD[0], 0.608331, 2.300004);
    TextDrawTextSize(TwitterMainTD[0], 298.500000, 49.000000);
    TextDrawSetOutline(TwitterMainTD[0], true);
    TextDrawSetShadow(TwitterMainTD[0], false);
    TextDrawAlignment(TwitterMainTD[0], 2);
    TextDrawColor(TwitterMainTD[0], -1);
    TextDrawBackgroundColor(TwitterMainTD[0], 255);
    TextDrawBoxColor(TwitterMainTD[0], -1);
    TextDrawUseBox(TwitterMainTD[0], true);
    TextDrawSetProportional(TwitterMainTD[0], true);
    TextDrawSetSelectable(TwitterMainTD[0], false);

    TwitterMainTD[1] = TextDrawCreate(567.000000, 261.000000, "Tweet");
    TextDrawFont(TwitterMainTD[1], true);
    TextDrawLetterSize(TwitterMainTD[1], 0.166666, 1.049998);
    TextDrawTextSize(TwitterMainTD[1], 598.000000, 15.000000);
    TextDrawSetOutline(TwitterMainTD[1], false);
    TextDrawSetShadow(TwitterMainTD[1], false);
    TextDrawAlignment(TwitterMainTD[1], true);
    TextDrawColor(TwitterMainTD[1], 255);
    TextDrawBackgroundColor(TwitterMainTD[1], 255);
    TextDrawBoxColor(TwitterMainTD[1], 50);
    TextDrawUseBox(TwitterMainTD[1], false);
    TextDrawSetProportional(TwitterMainTD[1], true);
    TextDrawSetSelectable(TwitterMainTD[1], true);

    TwitterMainTD[2] = TextDrawCreate(532.000000, 327.000000, "Ingatlah untuk selalu mematuhi persyaratan pengguna kami!");
    TextDrawFont(TwitterMainTD[2], true);
    TextDrawLetterSize(TwitterMainTD[2], 0.166666, 1.049998);
    TextDrawTextSize(TwitterMainTD[2], 620.500000, 97.000000);
    TextDrawSetOutline(TwitterMainTD[2], false);
    TextDrawSetShadow(TwitterMainTD[2], false);
    TextDrawAlignment(TwitterMainTD[2], true);
    TextDrawColor(TwitterMainTD[2], -1);
    TextDrawBackgroundColor(TwitterMainTD[2], 255);
    TextDrawBoxColor(TwitterMainTD[2], 50);
    TextDrawUseBox(TwitterMainTD[2], false);
    TextDrawSetProportional(TwitterMainTD[2], true);
    TextDrawSetSelectable(TwitterMainTD[2], false);

    TwitterMainTD[3] = TextDrawCreate(574.000000, 283.000000, "_");
    TextDrawFont(TwitterMainTD[3], false);
    TextDrawLetterSize(TwitterMainTD[3], 0.608331, 2.300004);
    TextDrawTextSize(TwitterMainTD[3], 298.500000, 49.000000);
    TextDrawSetOutline(TwitterMainTD[3], true);
    TextDrawSetShadow(TwitterMainTD[3], false);
    TextDrawAlignment(TwitterMainTD[3], 2);
    TextDrawColor(TwitterMainTD[3], -1);
    TextDrawBackgroundColor(TwitterMainTD[3], 255);
    TextDrawBoxColor(TwitterMainTD[3], -1);
    TextDrawUseBox(TwitterMainTD[3], true);
    TextDrawSetProportional(TwitterMainTD[3], true);
    TextDrawSetSelectable(TwitterMainTD[3], false);

    TwitterMainTD[4] = TextDrawCreate(566.000000, 287.000000, "Logout");
    TextDrawFont(TwitterMainTD[4], true);
    TextDrawLetterSize(TwitterMainTD[4], 0.166666, 1.049998);
    TextDrawTextSize(TwitterMainTD[4], 597.500000, 15.000000);
    TextDrawSetOutline(TwitterMainTD[4], false);
    TextDrawSetShadow(TwitterMainTD[4], false);
    TextDrawAlignment(TwitterMainTD[4], true);
    TextDrawColor(TwitterMainTD[4], 255);
    TextDrawBackgroundColor(TwitterMainTD[4], 255);
    TextDrawBoxColor(TwitterMainTD[4], 50);
    TextDrawUseBox(TwitterMainTD[4], false);
    TextDrawSetProportional(TwitterMainTD[4], true);
    TextDrawSetSelectable(TwitterMainTD[4], true);
}

CreateUberPhoneTD()
{
    UberPhoneTD[0] = TextDrawCreate(574.000000, 208.000000, "_");
	TextDrawFont(UberPhoneTD[0], 0);
	TextDrawLetterSize(UberPhoneTD[0], 0.608331, 22.300006);
	TextDrawTextSize(UberPhoneTD[0], 298.500000, 98.000000);
	TextDrawSetOutline(UberPhoneTD[0], 1);
	TextDrawSetShadow(UberPhoneTD[0], 0);
	TextDrawAlignment(UberPhoneTD[0], 2);
	TextDrawColor(UberPhoneTD[0], -1);
	TextDrawBackgroundColor(UberPhoneTD[0], 255);
	TextDrawBoxColor(UberPhoneTD[0], -1);
	TextDrawUseBox(UberPhoneTD[0], 1);
	TextDrawSetProportional(UberPhoneTD[0], 1);
	TextDrawSetSelectable(UberPhoneTD[0], 0);

	UberPhoneTD[1] = TextDrawCreate(531.000000, 357.000000, "Go again");
	TextDrawFont(UberPhoneTD[1], 1);
	TextDrawLetterSize(UberPhoneTD[1], 0.166666, 1.049998);
	TextDrawTextSize(UberPhoneTD[1], 590.000000, 103.500000);
	TextDrawSetOutline(UberPhoneTD[1], 0);
	TextDrawSetShadow(UberPhoneTD[1], 0);
	TextDrawAlignment(UberPhoneTD[1], 1);
	TextDrawColor(UberPhoneTD[1], 255);
	TextDrawBackgroundColor(UberPhoneTD[1], 255);
	TextDrawBoxColor(UberPhoneTD[1], 50);
	TextDrawUseBox(UberPhoneTD[1], 0);
	TextDrawSetProportional(UberPhoneTD[1], 1);
	TextDrawSetSelectable(UberPhoneTD[1], 0);

	UberPhoneTD[2] = TextDrawCreate(531.000000, 371.000000, "Work");
	TextDrawFont(UberPhoneTD[2], 1);
	TextDrawLetterSize(UberPhoneTD[2], 0.137499, 0.849997);
	TextDrawTextSize(UberPhoneTD[2], 590.000000, 103.500000);
	TextDrawSetOutline(UberPhoneTD[2], 0);
	TextDrawSetShadow(UberPhoneTD[2], 0);
	TextDrawAlignment(UberPhoneTD[2], 1);
	TextDrawColor(UberPhoneTD[2], 255);
	TextDrawBackgroundColor(UberPhoneTD[2], 255);
	TextDrawBoxColor(UberPhoneTD[2], 50);
	TextDrawUseBox(UberPhoneTD[2], 0);
	TextDrawSetProportional(UberPhoneTD[2], 1);
	TextDrawSetSelectable(UberPhoneTD[2], 0);

	UberPhoneTD[3] = TextDrawCreate(531.000000, 325.000000, "Rides");
	TextDrawFont(UberPhoneTD[3], 1);
	TextDrawLetterSize(UberPhoneTD[3], 0.166666, 1.049998);
	TextDrawTextSize(UberPhoneTD[3], 590.000000, 103.500000);
	TextDrawSetOutline(UberPhoneTD[3], 0);
	TextDrawSetShadow(UberPhoneTD[3], 0);
	TextDrawAlignment(UberPhoneTD[3], 1);
	TextDrawColor(UberPhoneTD[3], 255);
	TextDrawBackgroundColor(UberPhoneTD[3], 255);
	TextDrawBoxColor(UberPhoneTD[3], 50);
	TextDrawUseBox(UberPhoneTD[3], 0);
	TextDrawSetProportional(UberPhoneTD[3], 1);
	TextDrawSetSelectable(UberPhoneTD[3], 0);

	UberPhoneTD[4] = TextDrawCreate(578.000000, 325.000000, "Eats");
	TextDrawFont(UberPhoneTD[4], 1);
	TextDrawLetterSize(UberPhoneTD[4], 0.166666, 1.049998);
	TextDrawTextSize(UberPhoneTD[4], 599.000000, 103.500000);
	TextDrawSetOutline(UberPhoneTD[4], 0);
	TextDrawSetShadow(UberPhoneTD[4], 0);
	TextDrawAlignment(UberPhoneTD[4], 1);
	TextDrawColor(UberPhoneTD[4], 255);
	TextDrawBackgroundColor(UberPhoneTD[4], 255);
	TextDrawBoxColor(UberPhoneTD[4], 50);
	TextDrawUseBox(UberPhoneTD[4], 0);
	TextDrawSetProportional(UberPhoneTD[4], 1);
	TextDrawSetSelectable(UberPhoneTD[4], 0);

	UberPhoneTD[5] = TextDrawCreate(529.000000, 289.000000, "Preview_Model");
	TextDrawFont(UberPhoneTD[5], 5);
	TextDrawLetterSize(UberPhoneTD[5], 0.600000, 2.000000);
	TextDrawTextSize(UberPhoneTD[5], 43.000000, 52.500000);
	TextDrawSetOutline(UberPhoneTD[5], 0);
	TextDrawSetShadow(UberPhoneTD[5], 0);
	TextDrawAlignment(UberPhoneTD[5], 1);
	TextDrawColor(UberPhoneTD[5], -1);
	TextDrawBackgroundColor(UberPhoneTD[5], 60);
	TextDrawBoxColor(UberPhoneTD[5], 255);
	TextDrawUseBox(UberPhoneTD[5], 0);
	TextDrawSetProportional(UberPhoneTD[5], 1);
	TextDrawSetSelectable(UberPhoneTD[5], 1);
	TextDrawSetPreviewModel(UberPhoneTD[5], 410);
	TextDrawSetPreviewRot(UberPhoneTD[5], -10.000000, 0.000000, 33.000000, 1.000000);
	TextDrawSetPreviewVehCol(UberPhoneTD[5], 1, 1);

	UberPhoneTD[6] = TextDrawCreate(576.000000, 289.000000, "Preview_Model");
	TextDrawFont(UberPhoneTD[6], 5);
	TextDrawLetterSize(UberPhoneTD[6], 0.600000, 2.000000);
	TextDrawTextSize(UberPhoneTD[6], 43.000000, 52.500000);
	TextDrawSetOutline(UberPhoneTD[6], 0);
	TextDrawSetShadow(UberPhoneTD[6], 0);
	TextDrawAlignment(UberPhoneTD[6], 1);
	TextDrawColor(UberPhoneTD[6], -1);
	TextDrawBackgroundColor(UberPhoneTD[6], 60);
	TextDrawBoxColor(UberPhoneTD[6], 255);
	TextDrawUseBox(UberPhoneTD[6], 0);
	TextDrawSetProportional(UberPhoneTD[6], 1);
	TextDrawSetSelectable(UberPhoneTD[6], 1);
	TextDrawSetPreviewModel(UberPhoneTD[6], 2222);
	TextDrawSetPreviewRot(UberPhoneTD[6], -42.000000, 0.000000, 238.000000, 1.000000);
	TextDrawSetPreviewVehCol(UberPhoneTD[6], 1, 1);

	UberPhoneTD[7] = TextDrawCreate(531.000000, 379.000000, "1453 Michigan St.");
	TextDrawFont(UberPhoneTD[7], 1);
	TextDrawLetterSize(UberPhoneTD[7], 0.104166, 0.599997);
	TextDrawTextSize(UberPhoneTD[7], 590.000000, 103.500000);
	TextDrawSetOutline(UberPhoneTD[7], 0);
	TextDrawSetShadow(UberPhoneTD[7], 0);
	TextDrawAlignment(UberPhoneTD[7], 1);
	TextDrawColor(UberPhoneTD[7], -1094795521);
	TextDrawBackgroundColor(UberPhoneTD[7], 255);
	TextDrawBoxColor(UberPhoneTD[7], 50);
	TextDrawUseBox(UberPhoneTD[7], 0);
	TextDrawSetProportional(UberPhoneTD[7], 1);
	TextDrawSetSelectable(UberPhoneTD[7], 0);

	UberPhoneTD[8] = TextDrawCreate(595.000000, 210.000000, "Amber");
	TextDrawFont(UberPhoneTD[8], 1);
	TextDrawLetterSize(UberPhoneTD[8], 0.166666, 1.049998);
	TextDrawTextSize(UberPhoneTD[8], 7.000000, 23.500000);
	TextDrawSetOutline(UberPhoneTD[8], 0);
	TextDrawSetShadow(UberPhoneTD[8], 0);
	TextDrawAlignment(UberPhoneTD[8], 2);
	TextDrawColor(UberPhoneTD[8], -1);
	TextDrawBackgroundColor(UberPhoneTD[8], 255);
	TextDrawBoxColor(UberPhoneTD[8], 50);
	TextDrawUseBox(UberPhoneTD[8], 0);
	TextDrawSetProportional(UberPhoneTD[8], 1);
	TextDrawSetSelectable(UberPhoneTD[8], 0);

	UberPhoneTD[9] = TextDrawCreate(574.000000, 208.000000, "_");
	TextDrawFont(UberPhoneTD[9], 0);
	TextDrawLetterSize(UberPhoneTD[9], 0.608331, 1.650006);
	TextDrawTextSize(UberPhoneTD[9], 298.500000, 98.000000);
	TextDrawSetOutline(UberPhoneTD[9], 1);
	TextDrawSetShadow(UberPhoneTD[9], 0);
	TextDrawAlignment(UberPhoneTD[9], 2);
	TextDrawColor(UberPhoneTD[9], -1);
	TextDrawBackgroundColor(UberPhoneTD[9], 255);
	TextDrawBoxColor(UberPhoneTD[9], 1296911871);
	TextDrawUseBox(UberPhoneTD[9], 1);
	TextDrawSetProportional(UberPhoneTD[9], 1);
	TextDrawSetSelectable(UberPhoneTD[9], 0);

	UberPhoneTD[10] = TextDrawCreate(531.000000, 387.000000, "Lancy Apartment");
	TextDrawFont(UberPhoneTD[10], 1);
	TextDrawLetterSize(UberPhoneTD[10], 0.137499, 0.849997);
	TextDrawTextSize(UberPhoneTD[10], 590.000000, 103.500000);
	TextDrawSetOutline(UberPhoneTD[10], 0);
	TextDrawSetShadow(UberPhoneTD[10], 0);
	TextDrawAlignment(UberPhoneTD[10], 1);
	TextDrawColor(UberPhoneTD[10], 255);
	TextDrawBackgroundColor(UberPhoneTD[10], 255);
	TextDrawBoxColor(UberPhoneTD[10], 50);
	TextDrawUseBox(UberPhoneTD[10], 0);
	TextDrawSetProportional(UberPhoneTD[10], 1);
	TextDrawSetSelectable(UberPhoneTD[10], 0);

	UberPhoneTD[11] = TextDrawCreate(531.000000, 395.000000, "482 Riverside St.");
	TextDrawFont(UberPhoneTD[11], 1);
	TextDrawLetterSize(UberPhoneTD[11], 0.104166, 0.599997);
	TextDrawTextSize(UberPhoneTD[11], 590.000000, 103.500000);
	TextDrawSetOutline(UberPhoneTD[11], 0);
	TextDrawSetShadow(UberPhoneTD[11], 0);
	TextDrawAlignment(UberPhoneTD[11], 1);
	TextDrawColor(UberPhoneTD[11], -1094795521);
	TextDrawBackgroundColor(UberPhoneTD[11], 255);
	TextDrawBoxColor(UberPhoneTD[11], 50);
	TextDrawUseBox(UberPhoneTD[11], 0);
	TextDrawSetProportional(UberPhoneTD[11], 1);
	TextDrawSetSelectable(UberPhoneTD[11], 0);
}

CreatePlayerRebootTD(playerid)
{
    PhoneRebootBar[playerid] = CreatePlayerTextDraw(playerid, 550.000000, 319.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, PhoneRebootBar[playerid], 4);
	PlayerTextDrawLetterSize(playerid, PhoneRebootBar[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, PhoneRebootBar[playerid], 29.500000, 3.000000);
	PlayerTextDrawSetOutline(playerid, PhoneRebootBar[playerid], 1);
	PlayerTextDrawSetShadow(playerid, PhoneRebootBar[playerid], 0);
	PlayerTextDrawAlignment(playerid, PhoneRebootBar[playerid], 1);
	PlayerTextDrawColor(playerid, PhoneRebootBar[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, PhoneRebootBar[playerid], 255);
	PlayerTextDrawBoxColor(playerid, PhoneRebootBar[playerid], 50);
	PlayerTextDrawUseBox(playerid, PhoneRebootBar[playerid], 1);
	PlayerTextDrawSetProportional(playerid, PhoneRebootBar[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, PhoneRebootBar[playerid], 0);
}
CreatePlayerTwitterTD(playerid)
{
    TwitterInfoTD[playerid] = CreatePlayerTextDraw(playerid, 529.000000, 229.000000, "Hai, Mukhlis-Sadewa bagaimana harimu?");
    PlayerTextDrawFont(playerid, TwitterInfoTD[playerid], true);
    PlayerTextDrawLetterSize(playerid, TwitterInfoTD[playerid], 0.187499, 1.199997);
    PlayerTextDrawTextSize(playerid, TwitterInfoTD[playerid], 613.000000, 97.000000);
    PlayerTextDrawSetOutline(playerid, TwitterInfoTD[playerid], false);
    PlayerTextDrawSetShadow(playerid, TwitterInfoTD[playerid], false);
    PlayerTextDrawAlignment(playerid, TwitterInfoTD[playerid], true);
    PlayerTextDrawColor(playerid, TwitterInfoTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, TwitterInfoTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, TwitterInfoTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, TwitterInfoTD[playerid], false);
    PlayerTextDrawSetProportional(playerid, TwitterInfoTD[playerid], true);
    PlayerTextDrawSetSelectable(playerid, TwitterInfoTD[playerid], false);
}

CreatePlayerUberTD(playerid)
{
    UberMainTD[playerid][0] = CreatePlayerTextDraw(playerid, 528.000000, 240.000000, "Hello, Marcio Zentavious");
	PlayerTextDrawFont(playerid, UberMainTD[playerid][0], 1);
	PlayerTextDrawLetterSize(playerid, UberMainTD[playerid][0], 0.166666, 1.049998);
	PlayerTextDrawTextSize(playerid, UberMainTD[playerid][0], 620.500000, 103.500000);
	PlayerTextDrawSetOutline(playerid, UberMainTD[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, UberMainTD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, UberMainTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, UberMainTD[playerid][0], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, UberMainTD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, UberMainTD[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, UberMainTD[playerid][0], 0);
	PlayerTextDrawSetProportional(playerid, UberMainTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, UberMainTD[playerid][0], 0);

	UberMainTD[playerid][1] = CreatePlayerTextDraw(playerid, 529.000000, 252.000000, "What are you looking for today?");
	PlayerTextDrawFont(playerid, UberMainTD[playerid][1], 1);
	PlayerTextDrawLetterSize(playerid, UberMainTD[playerid][1], 0.166666, 1.049998);
	PlayerTextDrawTextSize(playerid, UberMainTD[playerid][1], 590.000000, 103.500000);
	PlayerTextDrawSetOutline(playerid, UberMainTD[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, UberMainTD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, UberMainTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, UberMainTD[playerid][1], 255);
	PlayerTextDrawBackgroundColor(playerid, UberMainTD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, UberMainTD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, UberMainTD[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, UberMainTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, UberMainTD[playerid][1], 0);
}