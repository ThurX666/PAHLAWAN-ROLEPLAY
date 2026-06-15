enum e_AnimationStuff
{
	e_AnimationName[32], //nama item
	e_AnimLib[32],
    e_AnimName[32],
    Float:e_AnimDelta,
    bool:e_AnimLoop,
    bool:e_AnimLX,
    bool:e_AnimLY,
    bool:e_AnimFreeze,
    e_AnimTime
};

new const g_AnimDetails[][e_AnimationStuff] =
{
    //animasi umum
    {"Angguk", "COP_AMBIENT","Copbrowse_nod", 4.1, true, false, false, true, 0},
    {"Angguk2", "COP_AMBIENT","Coplook_nod", 4.1, true, false, false, true, 0},
    {"Nonton", "OTB","wtchrace_cmon", 4.1, false, false, false, true, 0},
    {"Nonton2", "OTB","wtchrace_lose", 4.1, false, false, false, true, 0},
    {"Nonton3", "OTB","wtchrace_win", 4.1, false, false, false, true, 0},
    {"Tunggu", "COP_AMBIENT","Coplook_out", 4.1, true, false, false, true, 0},
    {"Tunggu2", "COP_AMBIENT","Coplook_shake", 4.1, true, false, false, true, 0},
    {"Pikir", "COP_AMBIENT","Coplook_think", 4.1, false, false, false, true, 0},
    {"Jam", "COP_AMBIENT","Coplook_watch", 4.1, false, false, false, true, 0},
    {"Onani", "PAULNMAC", "WANK_IN", 4.0, false, false, false, true, 0},
    {"Onani2", "PAULNMAC", "WANK_LOOP", 4.0, true, false, false, true, 0},
    {"Rokok", "SMOKING", "M_smk_in", 4.1, false, false, false, true, 0},
    {"Rokok2", "SMOKING","M_smklean_loop", 4.1, true, false, false, true, 0},
    {"Rokok3", "SMOKING","M_smk_tap",4.1, false, false, false, true, 0},
    {"Liptang", "COP_AMBIENT", "Coplook_loop", 4.1, false, true, true, true, 0},
    {"Liptang2","GRAVEYARD", "prst_loopa", 4.1, true, false, false, false, 0},
    {"Liptang3","GRAVEYARD", "mrnM_loop", 4.1, true, false, false, false, 0},
    {"Liptang4","DEALER", "DEALER_IDLE", 4.1, false, true, true, true, 0},
    {"Liptang5", "OTB","wtchrace_in", 4.1, false, false, false, true, 0},
    {"Liptang6", "OTB","wtchrace_loop", 4.1, true, false, false, true, 0},
    {"Duduk", "CRIB", "PED_Console_Loop", 4.1, true, false, false, false, 0},
    {"Duduk2", "INT_HOUSE", "LOU_In", 4.1, false, false, false, true, 0},
    {"Duduk3", "MISC", "SEAT_LR", 4.1, true, false, false, false, 0},
    {"Duduk4", "MISC", "Seat_talk_01", 4.1, true, false, false, false, 0},
    {"Duduk5", "MISC", "Seat_talk_02", 4.1, true, false, false, false, 0},
    {"Duduk6", "ped", "SEAT_down", 4.1, false, false, false, true, 0},
    {"Duduk7", "PED","SEAT_idle",4.1, false, false, false, true, 0},
    {"Duduk8", "JST_BUISNESS","girl_02",4.1, false, false, false, true, 0},
    {"Santai", "BEACH", "bather", 4.1, true, false, false, false, 0},
    {"Santai2", "BEACH", "Lay_Bac_Loop", 4.1, true, false, false, false, 0},
    {"Santai3", "BEACH", "ParkSit_M_loop", 4.1, true, false, false, false, 0},
    {"Santai4", "BEACH", "ParkSit_W_loop", 4.1, true, false, false, false, 0},
    {"Santai5", "BEACH", "SitnWait_loop_W", 4.1, true, false, false, false, 0},
    {"Turu", "CRACK", "crckdeth4", 4.1, false, false, false, true, 0},
    {"Turu2", "CRACK", "crckidle4", 4.1, false, false, false, true, 0},
    {"Olahraga", "benchpress", "gym_bp_celebrate", 4.1, false, false, false, false, 0},
    {"Olahraga2", "benchpress", "gym_bp_down", 4.1, false, false, false, true, 0},
    {"Olahraga3", "benchpress", "gym_bp_getoff", 4.1, false, false, false, false, 0},
    {"Olahraga4", "benchpress", "gym_bp_geton", 4.1, false, false, false, true, 0},
    {"Olahraga5", "benchpress", "gym_bp_up_A", 4.1, false, false, false, true, 0},
    {"Olahraga6", "benchpress", "gym_bp_up_B", 4.1, false, false, false, true, 0},
    {"Olahraga7", "benchpress", "gym_bp_up_smooth", 4.1, false, false, false, true, 0},
    {"Olahraga8", "GYMNASIUM", "GYMshadowbox", 4.0, true, true, true, true, 0},
    {"Yoga", "PARK", "Tai_Chi_Loop", 4.1, true, false, false, false, 0},
    {"Yoga2", "DAM_JUMP", "DAM_Dive_Loop", 4.1, true, false, false, false, 0},
    {"Loncat", "DODGE", "Crush_Jump", 4.1, false, true, true, false, 0},
    {"Muntah", "FOOD", "EAT_Vomit_P", 4.1, false, false, false, false, 0},
    {"Mabok", "PED", "WALK_drunk", 4.1, true, true, true, true, 1},
    {"Hormat", "GHANDS", "gsign5LH", 4.1, false, false, false, false, 0},
    {"Chat", "GANGS", "prtial_gngtlkA", 4.1, false, false, false, false, 0},
    {"Chat2", "GANGS", "prtial_gngtlkB", 4.1, false, false, false, false, 0},
    {"Chat3", "GANGS", "prtial_gngtlkE", 4.1, false, false, false, false, 0},
    {"Chat4", "GANGS", "prtial_gngtlkF", 4.1, false, false, false, false, 0},
    {"Chat5", "GANGS", "prtial_gngtlkG", 4.1, false, false, false, false, 0},
    {"Chat6", "GANGS", "prtial_gngtlkH", 4.1, false, false, false, false, 0},
    {"Lambai", "PED", "endchat_03", 4.1, false, false, false, false, 0},
    {"Lambai2", "KISSING", "gfwave2", 4.1, false, false, false, false, 0},
    {"Lambai3", "ON_LOOKERS", "wave_loop", 4.1, true, false, false, false, 0},
    {"Nangis", "GRAVEYARD", "mrnF_loop", 4.1, true, false, false, true, 0},
    {"Nangis2", "GRAVEYARD", "MRNM_LOOP", 4.0, true, false, false, true, 0},
    {"Tawa", "RAPPING", "Laugh_01", 4.0, false, false, false, true, 0},
    {"Salam", "ON_LOOKERS","Pointup_loop",4.1, false, false, false, true, 0},
    {"Tegur", "ON_LOOKERS","Pointup_loop",4.1, false, false, false, true, 0},
    {"Hitch", "ON_LOOKERS","Pointup_loop",4.1, false, false, false, true, 0},
    {"Lelah", "PED", "IDLE_tired", 4.1, true, false, false, false, 0},
    {"Lelah2", "FAT", "IDLE_tired", 4.1, true, false, false, false, 0},
    {"Jarteng", "PED", "fucku", 4.1, false, false, false, false, 0},
    {"Rap", "RAPPING", "RAP_A_Loop", 4.1, true, false, false, false, 0},
    {"Rap2", "RAPPING", "RAP_B_Loop", 4.1, true, false, false, false, 0},
    {"Rap3", "RAPPING", "RAP_C_Loop", 4.1, true, false, false, false, 0},
    {"Senam", "SKATE", "skate_idle", 4.1, true, false, false, false, 0},
    {"Striptis", "STRIP", "strip_A", 4.1, true, false, false, false, 0},
    {"Striptis2", "STRIP", "strip_B", 4.1, true, false, false, false, 0},
    {"Striptis3", "STRIP", "strip_C", 4.1, true, false, false, false, 0},
    {"Striptis4", "STRIP", "strip_D", 4.1, true, false, false, false, 0},
    {"Striptis5", "STRIP", "strip_E", 4.1, true, false, false, false, 0},
    {"Striptis6", "STRIP", "strip_F", 4.1, true, false, false, false, 0},
    {"Striptis7", "STRIP", "strip_G", 4.1, true, false, false, false, 0},
    {"Striptis8", "STRIP", "STR_A2B", 4.1, true, false, false, false, 0},
    {"Striptis9", "STRIP", "STR_B2C", 4.1, true, false, false, false, 0},
    {"Striptis10", "STRIP", "STR_C1", 4.1, true, false, false, false, 0},
    {"Striptis11", "STRIP", "STR_C2", 4.1, true, false, false, false, 0},
    {"Striptis12", "STRIP", "STR_Loop_A", 4.1, true, false, false, false, 0},
    {"Striptis13", "STRIP", "STR_Loop_B", 4.1, true, false, false, false, 0},
    {"Striptis14", "STRIP", "STR_Loop_C", 4.1, true, false, false, false, 0},
    {"Sorak", "ON_LOOKERS", "shout_01", 4.1, false, false, false, false, 0},
    {"Sorak2", "ON_LOOKERS", "shout_02", 4.1, false, false, false, false, 0},
    {"Sorak3","ON_LOOKERS", "shout_in", 4.1, false, false, false, false, 0},
    {"Sorak4", "RIOT", "RIOT_ANGRY_B", 4.1, true, false, false, false, 0},
    {"Sorak5", "RIOT", "RIOT_CHANT", 4.1, false, false, false, false, 0},
    {"Sorak6", "RIOT", "RIOT_shout", 4.1, false, false, false, false, 0},
    {"Sorak7", "STRIP", "PUN_HOLLER", 4.1, false, false, false, false, 0},
    {"Sorak8", "OTB", "wtchrace_win", 4.1, false, false, false, false, 0},
    {"Garuk", "SCRATCHING", "scdldlp", 4.1, true, false, false, false, 0},
    {"Garuk2", "SCRATCHING", "scdlulp", 4.1, true, false, false, false, 0},
    {"Garuk3", "SCRATCHING", "scdrdlp", 4.1, true, false, false, false, 0},
    {"Garuk4", "SCRATCHING", "scdrulp", 4.1, true, false, false, false, 0},
    {"Tikam", "KNIFE", "knife_1", 4.1, false, true, true, false, 0},
    {"Tikam2", "KNIFE", "knife_2", 4.1, false, true, true, false, 0},
    {"Tikam3", "KNIFE", "knife_3", 4.1, false, true, true, false, 0},
    {"Tikam4", "KNIFE", "knife_4", 4.1, false, true, true, false, 0},
    {"Tikam5", "KNIFE", "WEAPON_knifeidle", 4.1, true, false, false, false, 0},
    {"Tikam6", "KNIFE", "KILL_Knife_Player", 4.1, false, false, false, false, 0},
    {"Tikam7", "KNIFE", "KILL_Knife_Ped_Damage", 4.1, false, false, false, false, 0},
    {"Tikam8", "KNIFE", "KILL_Knife_Ped_Die", 4.1, false, false, false, false, 0},
    {"Joget", "DANCING", "dance_loop", 4.1, true, false, false, false, 0},
    {"Joget2", "DANCING", "DAN_Left_A", 4.1, true, false, false, false, 0},
    {"Joget3", "DANCING", "DAN_Right_A", 4.1, true, false, false, false, 0},
    {"Joget4", "DANCING", "DAN_Loop_A", 4.1, true, false, false, false, 0},
    {"Joget5", "DANCING", "DAN_Up_A", 4.1, true, false, false, false, 0},
    {"Joget6", "DANCING", "DAN_Down_A", 4.1, true, false, false, false, 0},
    {"Joget7", "DANCING", "dnce_M_a", 4.1, true, false, false, false, 0},
    {"Joget8", "DANCING", "dnce_M_e", 4.1, true, false, false, false, 0},
    {"Joget9", "DANCING", "dnce_M_b", 4.1, true, false, false, false, 0},
    {"Joget10", "DANCING", "dnce_M_c", 4.1, true, false, false, false, 0},
    {"Makan", "FOOD", "EAT_Burger", 4.1, false, false, false, false, 0},
    {"Makan2", "FOOD", "EAT_Chicken", 4.1, false, false, false, false, 0},
    {"Makan3", "FOOD", "EAT_Pizza", 4.1, false, false, false, false, 0},
    {"Deal", "DEALER", "DEALER_DEAL", 4.1, false, false, false, false, 0},
    {"Deal2", "DEALER", "DRUGS_BUY", 4.1, false, false, false, false, 0},
    {"Deal3", "DEALER", "shop_pay", 4.1, false, false, false, false, 0},
    {"Deal4", "DEALER", "DEALER_IDLE_01", 4.1, true, false, false, false, 0},
    {"Deal5", "DEALER", "DEALER_IDLE_02", 4.1, true, false, false, false, 0},
    {"Deal6", "DEALER", "DEALER_IDLE_03", 4.1, true, false, false, false, 0},
    {"Kejang", "CRACK", "crckdeth1", 4.1, false, false, false, true, 0},
    {"Kejang2", "CRACK", "crckdeth2", 4.1, true, false, false, false, 0},
    {"Kejang3", "CRACK", "crckdeth3", 4.1, false, false, false, true, 0},
    {"Kejang4", "CRACK", "crckidle1", 4.1, false, false, false, true, 0},
    {"Kejang5", "CRACK", "crckidle2", 4.1, false, false, false, true, 0},
    {"Kejang6", "CRACK", "crckidle3", 4.1, false, false, false, true, 0},
    {"Angkat", "CARRY", "liftup", 4.1, false, false, false, false, 0},
    {"Angkat2", "CARRY", "liftup05", 4.1, false, false, false, false, 0},
    {"Angkat3", "CARRY", "liftup105", 4.1, false, false, false, false, 0},
    {"Letak", "CARRY", "putdwn", 4.1, false, false, false, false, 0},
    {"Letak2", "CARRY", "putdwn05", 4.1, false, false, false, false, 0},
    {"Letak3", "CARRY", "putdwn105", 4.1, false, false, false, false, 0},
    {"Gesek", "BOMBER", "BOM_Plant", 4.1, false, false, false, false, 0},
    {"Servis", "CAR", "Fixn_Car_Loop", 4.1, true, false, false, true, 0},
    {"Servis2", "CAR", "Fixn_Car_Out", 4.1, false, false, false, true, 1},
    {"Bartender", "BAR", "Barserve_bottle", 4.1, false, false, false, false, 0},
    {"Bartender2", "BAR", "Barserve_give", 4.1, false, false, false, false, 0},
    {"Bartender3", "BAR", "Barserve_glass", 4.1, false, false, false, false, 0},
    {"Bartender4", "BAR", "Barserve_in", 4.1, false, false, false, false, 0},
    {"Bartender5", "BAR", "Barserve_order", 4.1, false, false, false, false, 0},
    {"Bartender6", "BAR", "BARman_idle", 4.1, true, false, false, false, 0},
    {"Bartender7", "BAR", "dnk_stndM_loop", 4.1, false, false, false, false, 0},
    {"Bartender8", "BAR", "dnk_stndF_loop", 4.1, false, false, false, false, 0},
    {"Kacamata", "goggles", "goggles_put_on", 4.1, false, false, false, false, 0},
    {"Semprot", "GRAFFITI", "spraycan_fire", 4.1, true, false, false, false, 0},
    {"Lempar", "GRENADE", "WEAPON_throw", 4.1, false, false, false, false, 0},
    {"Ped", "FAT", "FatWalk", 4.1, true, true, true, true, 1},
    {"Ped2", "MUSCULAR", "MuscleWalk", 4.1, true, true, true, true, 1},
    {"Ped3", "PED", "WALK_armed", 4.1, true, true, true, true, 1},
    {"Ped4", "PED", "WALK_civi", 4.1, true, true, true, true, 1},
    {"Ped5", "PED", "WALK_fat", 4.1, true, true, true, true, 1},
    {"Ped6", "PED", "WALK_fatold", 4.1, true, true, true, true, 1},
    {"Ped7", "PED", "WALK_gang1", 4.1, true, true, true, true, 1},
    {"Ped8", "PED", "WALK_gang2", 4.1, true, true, true, true, 1},
    {"Ped9", "PED", "WALK_player", 4.1, true, true, true, true, 1},
    {"Ped10", "PED", "WALK_old", 4.1, true, true, true, true, 1},
    {"Ped11", "PED", "WALK_wuzi", 4.1, true, true, true, true, 1},
    {"Ped12", "PED", "WOMAN_walkbusy", 4.1, true, true, true, true, 1},
    {"Ped13", "PED", "WOMAN_walkfatold", 4.1, true, true, true, true, 1},
    {"Ped14", "PED", "WOMAN_walknorm", 4.1, true, true, true, true, 1},
    {"Ped15", "PED", "WOMAN_walksexy", 4.1, true, true, true, true, 1},
    {"Ped16", "PED", "WOMAN_walkshop", 4.1, true, true, true, true, 1},

    {"Camera", "CAMERA", "camcrch_idleloop", 2.0, true, false, false, false, 0},
    {"Camera2", "CAMERA", "piccrch_take", 1.0, true, false, false, false, 0},
    {"Camera3", "CAMERA", "picstnd_take", 1.0, true, false, false, false, 0},
    {"Camera4", "CAMERA", "piccrch_in", 1.33, true, false, false, false, 0},
    {"Camera5", "CAMERA", "picstnd_in", 1.0, true, false, false, false, 0},

    {"Sandar", "SMOKING","M_smklean_loop", 4.1, true, false, false, true, 0},
    {"Sandar2", "GANGS","leanIDLE", 1.0, true, false, false, true, 0},
    {"Sandar3", "MISC","Plyrlean_loop", 2.67, true, false, false, true, 0},
    {"Sandar4", "SHOP","Smoke_RYD", 6.67, true, false, false, true, 0},
    {"Sandar5", "WEAPONS","SHP_Tray_Pose", 2.67, false, false, false, true, 0},
    {"Geleng", "MISC","plyr_shkhead", 1.67, true, false, false, true, 0},

    {"Basket", "BSKTBALL","BBALL_def_jump_shot", 1.17, true, false, false, true, 0},
    {"Basket2", "BSKTBALL","BBALL_def_loop", 1.00, true, false, false, true, 0},
    {"Basket3", "BSKTBALL","BBALL_def_stepL", 0.60, true, false, false, true, 0},
    {"Basket4", "BSKTBALL","BBALL_def_stepR", 0.60, true, false, false, true, 0},
    {"Basket5", "BSKTBALL","BBALL_Dnk", 1.40, true, false, false, true, 0},
    {"Basket6", "BSKTBALL","BBALL_Dnk_Gli", 0.37, true, false, false, true, 0},
    {"Basket7", "BSKTBALL","BBALL_Dnk_Lnch", 0.20, true, false, false, true, 0},
    {"Basket8", "BSKTBALL","BBALL_idle", 2.43, true, false, false, true, 0},
    {"Basket9", "BSKTBALL","BBALL_idle2", 2.67, true, false, false, true, 0},
    {"Basket10", "BSKTBALL","BBALL_idleloop", 0.67, true, false, false, true, 0},
    {"Basket11", "BSKTBALL","BBALL_Jump_Shot", 1.67, true, false, false, true, 0},
    {"Basket12", "BSKTBALL","BBALL_run", 0.90, true, true, true, true, 0},
    {"Basket13", "BSKTBALL","BBALL_walk", 1.07, true, true, true, true, 0},
    
    //animasi perampokan / gangster
    {"Angtang", "ROB_BANK","SHP_HandsUp_Scr", 4.1, false, false, false, true, 0},
    {"Geledah", "BD_FIRE","wash_up", 4.1, true, false, false, true, 0},
    {"Geledah2", "POLICE", "plc_drgbst_01", 4.1, false, false, false, true, 0},
    {"Geledah3", "POLICE", "plc_drgbst_02", 4.1, false, false, false, true, 0},
    {"Diperiksa", "POLICE", "crm_drgbst_01", 4.1, false, false, false, true, 0},
    {"Terlentang", "PED","KO_skid_front", 4.1, false, false, false, true, 0},
    {"Tiarap", "PED","FLOOR_hit_f", 4.1, false, false, false, true, 0},
    {"Nunduk", "PED", "cower", 4.1, false, false, false, true, 0},
    {"Nodong", "PED", "ARRESTgun", 4.1, false, false, false, true, 0},
    {"Nodong2", "SHOP", "ROB_Loop_Threat", 4.1, true, false, false, false, 0},
    {"Nodong3", "ON_LOOKERS", "point_loop", 4.1, true, false, false, false, 0},
    {"Nodong4", "ON_LOOKERS", "Pointup_loop", 4.1, true, false, false, false, 0},
    {"Geng", "GHANDS", "gsign1", 4.1, true, false, false, false, 0},
    {"Geng2","GHANDS", "gsign1LH", 4.1, true, false, false, false, 0},
    {"Geng3","GHANDS", "gsign2", 4.1, true, false, false, false, 0},
    {"Geng4","GHANDS", "gsign2LH", 4.1, true, false, false, false, 0},
    {"Geng5","GHANDS", "gsign3", 4.1, true, false, false, false, 0},
    {"Geng6","GHANDS", "gsign3LH", 4.1, true, false, false, false, 0},
    {"Geng7","GHANDS", "gsign4", 4.1, true, false, false, false, 0},
    {"Geng8","GHANDS", "gsign4LH", 4.1, true, false, false, false, 0},
    {"Geng9","GHANDS", "gsign5", 4.1, true, false, false, false, 0},
    {"Geng10", "GHANDS", "gsign5", 4.1, true, false, false, false, 0},
    {"Geng11", "GHANDS", "gsign5LH", 4.1, true, false, false, false, 0},
    {"Geng12", "GANGS", "Invite_No", 4.1, true, false, false, false, 0},
    {"Geng13", "GANGS", "Invite_Yes", 4.1, true, false, false, false, 0},
    {"Geng14", "GANGS", "prtial_gngtlkD", 4.1, true, false, false, false, 0},
    {"Geng15", "GANGS", "smkcig_prtl", 4.1, true, false, false, false, 0},
    {"Terluka", "SWEET", "Sweet_injuredloop", 4.0, true, false, false, true, 0},
    {"Tertembak", "PED","KO_shot_stom",4.1, false, false, false, true, 0},
    {"Kode", "GANGS", "hndshkba", 4.1, false, false, false, true, 0},
    {"Kode2", "GANGS", "hndshkda", 4.1, false, false, false, true, 0},
    {"Kode3", "GANGS", "hndshkfa_swt", 4.1, false, false, false, true, 0},
    {"Dorong", "GANGS","shake_cara",4.1, false, false, false, true, 0},
    {"Dorong2", "GANGS","shake_carSH",4.1, true, false, false, true, 0},

    //animasi bucin
    {"Kiss", "KISSING", "Grlfrd_Kiss_01", 4.1, false, false, false, false, 0},
    {"Kiss2", "KISSING", "Grlfrd_Kiss_02", 4.1, false, false, false, false, 0},
    {"Kiss3", "KISSING", "Grlfrd_Kiss_03", 4.1, false, false, false, false, 0},
    {"Kiss4", "KISSING", "Playa_Kiss_01", 4.1, false, false, false, false, 0},
    {"Kiss5", "KISSING", "Playa_Kiss_02", 4.1, false, false, false, false, 0},
    {"Kiss6", "KISSING", "Playa_Kiss_03", 4.1, false, false, false, false, 0},
    {"Kulum", "BLOWJOBZ", "BJ_COUCH_LOOP_W", 4.1, true, false, false, false, 0},
    {"Kulum2", "BLOWJOBZ", "BJ_COUCH_LOOP_P", 4.1, true, false, false, false, 0},
    {"Kulum3", "BLOWJOBZ", "BJ_STAND_LOOP_W", 4.1, true, false, false, false, 0},
    {"Kulum4", "BLOWJOBZ", "BJ_STAND_LOOP_P", 4.1, true, false, false, false, 0},

    //animasi faction polda
    {"Borgol", "BD_FIRE","wash_up",4.1, true, false, false, true, 0},
    {"Mukul", "BASEBALL", "Bat_1", 4.1, false, true, true, false, 0},
    {"Mukul2","BASEBALL", "Bat_2", 4.1, false, true, true, false, 0},
    {"Mukul3","BASEBALL", "Bat_3", 4.1, false, true, true, false, 0},
    {"Mukul4","BASEBALL", "Bat_4", 4.1, false, false, false, false, 0},
    {"Kasti", "BASEBALL", "Bat_IDLE", 4.1, true, false, false, false, 0},
    {"Nangkis", "BASEBALL", "Bat_BLOCK", 4.1, true, false, false, false, 0},
    {"Kokang", "BUDDY", "buddy_reload", 4.1, false, false, false, false, 0},
    {"Kokang2", "UZI", "UZI_reload", 4.1, false, false, false, false, 0},
    {"Kokang3", "COLT45", "colt45_reload", 4.1, false, false, false, false, 0},
    {"Kokang4", "RIFLE", "rifle_load", 4.1, false, false, false, false, 0},
    {"Kantor", "INT_OFFICE", "OFF_Sit_Bored_Loop", 4.1, true, false, false, false, 0},
    {"Kantor2", "INT_OFFICE", "OFF_Sit_Crash", 4.1, true, false, false, false, 0},
    {"Kantor3", "INT_OFFICE", "OFF_Sit_Drink", 4.1, true, false, false, false, 0},
    {"Kantor4", "INT_OFFICE", "OFF_Sit_Read", 4.1, true, false, false, false, 0},
    {"Kantor5", "INT_OFFICE", "OFF_Sit_Type_Loop", 4.1, true, false, false, false, 0},
    {"Kantor6", "INT_OFFICE", "OFF_Sit_Watch", 4.1, true, false, false, false, 0},
    {"Akses", "HEIST9", "Use_SwipeCard", 4.1, false, false, false, false, 0},
    {"Pakpol", "POLICE", "CopTraf_Come", 4.0, true, false, false, false, 0},
    {"Pakpol2", "POLICE", "CopTraf_Away", 4.0, true, false, false, false, 0},
    {"Pakpol3", "POLICE", "CopTraf_Stop", 4.0, true, false, false, false, 0},
    {"Pakpol4", "POLICE", "CopTraf_Left", 4.0, true, false, false, false, 0},
    {"Tabok", "BASEBALL", "Bat_M", 4.1, false, false, false, false, 0},
    {"Tabok2", "MISC","bitchslap",4.1, true, false, false, true, 0},
    {"Tabok3", "SWEET","sweet_ass_slap",4.1, false, false, false, true, 0},
    {"Tabok4", "FLOWERS", "FLOWER_ATTACK_M", 4.0, false, false, false, true, 0},
    {"Dobrak", "POLICE","Door_Kick",4.1, false, false, false, true, 0},

    {"Cek", "COP_AMBIENT","Copbrowse_in", 4.1, false, false, false, false, 0},
    {"Cek2", "COP_AMBIENT","Copbrowse_loop", 4.1, true, false, false, true, 0},
    {"Cek3", "COP_AMBIENT","Copbrowse_out", 4.1, false, false, false, false, 0},
    {"Tulis", "OTB","betslp_loop", 4.1, true, false, false, true, 0},
    {"Tulis2", "OTB","betslp_tnk", 4.1, true, false, false, true, 0},

    {"Jetpack", "ped","Jetpack_Idle", 4.1, false, false, false, true, 0}
};

enum e_AnimPropStuff
{
	e_AnimationPropName[32], //nama item
	e_AnimPropLib[32],
    e_AnimPropName[32],
    Float:e_AnimPropDelta,
    bool:e_AnimPropLoop,
    bool:e_AnimPropLX,
    bool:e_AnimPropLY,
    bool:e_AnimPropFreeze,
    e_AnimPropTime,

    //prop object
    e_AnimPropIndex,
    e_AnimPropModel,
    e_AnimPropBone,
    Float:e_AnimPropOffX,
    Float:e_AnimPropOffY,
    Float:e_AnimPropOffZ,
    Float:e_AnimPropRotX,
    Float:e_AnimPropRotY,
    Float:e_AnimPropRotZ,
    Float:e_AnimPropScaX,
    Float:e_AnimPropScaY,
    Float:e_AnimPropScaZ,
    e_AnimPropMatCol0,
    e_AnimPropMatCol1
};

new const g_AnimPropDetails[][e_AnimPropStuff] =
{
    {"Box"},
    {"Box2"},
    {"Box3"},
    {"Ban"},
    {"Bumper"},
    {"Bumper2"},
    {"Toolbox"},
    {"Koper"},
    {"Bunga", "KISSING", "gift_give", 5.33, false, false, false, false, 0, 9, 325, 6, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Dildo", "PAULNMAC", "WANK_LOOP", 4.0, true, false, false, true, 0, 9, 321, 5, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Dildo2", "PAULNMAC", "WANK_LOOP", 4.0, true, false, false, true, 0, 9, 322, 5, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Bat", "CRACK", "Bbalbat_Idle_01", 6.67, true, false, false, true, 0, 9, 336, 6, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Bat2", "CRACK", "Bbalbat_Idle_02", 10.00, true, false, false, true, 0, 9, 336, 6, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Baton", "CRACK", "Bbalbat_Idle_01", 6.67, true, false, false, true, 0, 9, 334, 6, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Baton2", "CRACK", "Bbalbat_Idle_02", 10.00, true, false, false, true, 0, 9, 334, 6, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Skate", "ped","Jetpack_Idle", 4.1, false, false, false, true, 0, 9, 19878, 5, 0.016000, 0.028000, 0.456000, 0.400000, 91.400108, -1.100000, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Mic", "ped","Jetpack_Idle", 4.1, false, false, false, true, 0, 9, 19610, 5, 0.051999, 0.028999, -0.020000, -84.299865, -0.799999, 10.899998, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Bendera", "ped","Jetpack_Idle", 4.1, false, false, false, true, 0, 9, 11245, 5, -0.097999, 0.039000, 0.091999, 1.500000, 103.000022, -2.900001, 0.384999, 0.204000, 0.276000, 0, 0},
    {"Gitar", "CRACK", "Bbalbat_Idle_01", 6.67, true, false, false, true, 0, 9, 19317, 1, -0.145000, 0.356999, 0.211999, -9.399999, 25.299961, 154.199905, 1.000000, 1.051999, 1.000000, 0, 0},

    {"Kursi", "ped", "SEAT_down", 4.1, false, false, false, true, 0, 9, 1369, 1, -0.207000, 0.101999, -0.010000, -88.599967, 100.600143, -94.200103, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Kursi2",  "ped", "SEAT_down", 4.1, false, false, false, true, 0, 9, 2121, 1, -0.324999, 0.050000, -0.015000, -128.700027, 94.600151, -55.500225, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Camera", "CAMERA", "piccrch_take", 1.0, true, false, false, false, 0, 9, 19623, 6, 0.074999, 0.112999, 0.079999, 0.000000, 0.000000, 96.599990, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Camera2", "CAMERA", "picstnd_take", 1.0, true, false, false, false, 0, 9, 19623, 6, 0.152000, 0.068999, 0.037999, 3.899933, -0.499996, 91.399879, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Payung", "ped","Jetpack_Idle", 4.1, false, false, false, true, 0, 9, 642, 5, -0.279000, 0.126000, -0.356999, 19.699987, -134.099990, 1.599998, 0.368000, 0.371000, 0.470999, 0xFF3A3B3C, 0xFF3A3B3C},
    {"Basket", "BSKTBALL","BBALL_idleloop", 0.67, true, false, false, true, 0, 9, 2114, 6, 0.300000, 0.000000, 0.039999, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Basket2", "BSKTBALL","BBALL_run", 0.90, true, true, true, true, 0, 9, 2114, 6, 0.300000, 0.000000, 0.039999, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Basket3", "BSKTBALL","BBALL_walk", 1.07, true, true, true, true, 0, 9, 2114, 6, 0.300000, 0.000000, 0.039999, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Medbox", "CAMERA", "camcrch_idleloop", 2.0, true, false, false, false, 0, 9, 11738, 1, -0.522999, 0.668999, 0.550999, 74.799995, 76.100028, -21.699998, 1.473999, 1.431999, 1.212000, 0, 0},
    
    {"Buku", "ped","Jetpack_Idle", 4.1, false, false, false, true, 0, 9, 2894, 5, 0.063999, 0.051999, -0.043999, -148.800201, -3.600002, -71.900009, 0.395999, 0.459000, 1.089000, 0, 0},
    {"Senter", "GHETTO_DB","GDB_Car_RYD", 4.1, true, false, false, true, 0, 9, 18641, 6, 0.047999, 0.046000, -0.016999, 68.300003, 40.200000, 0.000000, 1.000000, 1.000000, 1.000000, 0, 0},
    {"Tablet", "INT_SHOP","shop_loop", 4.1, true, false, false, true, 0, 9, 19786, 5, 0.182999, 0.048999, -0.112999, -66.699935, -23.799949, -116.699996, 0.130999, 0.136000, 0.142000, 0, 0}
};

new const g_AnimSharedName[][] =
{
    "Cipok",
    "Cipok2",
    "Cipok3",
    "Gift",
    "Nikmat",
    "Nikmat2",
    "Salam",
    "Salam2",
    "Salam3",
    "Salam4",
    "Salam5",
    "Salam6",
    "Salam7"
};

GetListAnimName(playerid, const name[])
{
    for(new i; i < sizeof(g_AnimDetails); i ++)
    {
        if(!strcmp(g_AnimDetails[i][e_AnimationName], name, true))
        {
            gPlayerUsingLoopingAnim[playerid] = true;
            return ApplyAnimation(playerid, g_AnimDetails[i][e_AnimLib], g_AnimDetails[i][e_AnimName], g_AnimDetails[i][e_AnimDelta], g_AnimDetails[i][e_AnimLoop], g_AnimDetails[i][e_AnimLX], g_AnimDetails[i][e_AnimLY], g_AnimDetails[i][e_AnimFreeze], g_AnimDetails[i][e_AnimTime], true);
        }
    }
    ShowTDN(playerid, NOTIFICATION_ERROR, "Nama animasi tersebut tidak terdaftar!");
	return 1;
}

GetListPropAnimName(playerid, const name[])
{
    for(new i; i < sizeof(g_AnimPropDetails); i ++)
    {
        if(!strcmp(g_AnimPropDetails[i][e_AnimationPropName], name, true))
        {
            gPlayerUsingLoopingAnim[playerid] = true;
            SetPlayerAttachedObject(playerid, g_AnimPropDetails[i][e_AnimPropIndex], g_AnimPropDetails[i][e_AnimPropModel], g_AnimPropDetails[i][e_AnimPropBone], g_AnimPropDetails[i][e_AnimPropOffX], g_AnimPropDetails[i][e_AnimPropOffY], g_AnimPropDetails[i][e_AnimPropOffZ], g_AnimPropDetails[i][e_AnimPropRotX], g_AnimPropDetails[i][e_AnimPropRotY], g_AnimPropDetails[i][e_AnimPropRotZ], g_AnimPropDetails[i][e_AnimPropScaX], g_AnimPropDetails[i][e_AnimPropScaY], g_AnimPropDetails[i][e_AnimPropScaZ], g_AnimPropDetails[i][e_AnimPropMatCol0], g_AnimPropDetails[i][e_AnimPropMatCol1]);
            return ApplyAnimation(playerid, g_AnimPropDetails[i][e_AnimPropLib], g_AnimPropDetails[i][e_AnimPropName], g_AnimPropDetails[i][e_AnimPropDelta], g_AnimPropDetails[i][e_AnimPropLoop], g_AnimPropDetails[i][e_AnimPropLX], g_AnimPropDetails[i][e_AnimPropLY], g_AnimPropDetails[i][e_AnimPropFreeze], g_AnimPropDetails[i][e_AnimPropTime], true);
        }
    }
    ShowTDN(playerid, NOTIFICATION_ERROR, "Nama animasi tersebut tidak terdaftar!");
	return 1;
}

SyncAnimPage(playerid) 
{
    if(animPage[playerid] * 10 >= sizeof(g_AnimDetails)) 
    {
        for(new i; i < 10; i++) 
        {
            new index = (animPage[playerid] * 10) + i - 10;
            if (index >= sizeof(g_AnimDetails)) 
            {
                PlayerTextDrawHide(playerid, EmotesPTD[playerid][i]);
            }
        }
    }
    PlayerTextDrawSetString(playerid, EmotesPTD[playerid][10], sprintf("%02d / %02d", animPage[playerid], sizeof(g_AnimDetails)/10 + 1));
    return 1;
}

// SyncAnimPage(playerid) 
// {
//     if (animPage[playerid] * 10 >= sizeof(g_AnimDetails))
//     {
//         for(new i; i < 10; i++) 
//         {
//             new index = (animPage[playerid] * 10) + i;
//             PlayerTextDrawSetString(playerid, EmotesPTD[playerid][i], g_AnimDetails[index][e_AnimationName]);
//         }
//     }
//     PlayerTextDrawSetString(playerid, EmotesPTD[playerid][10], sprintf("%02d / %02d", animPage[playerid], sizeof(g_AnimDetails)));
//     return 1;
// }

YCMD:e(playerid, params[], help)
{
    if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    if(IsPlayerStunned(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(AccountData[playerid][pCuffed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(OJailData[playerid][jailed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(AccountData[playerid][pBlindfolded]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(AccountData[playerid][pInEvent]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    if(pPorterCarrying[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");

    static animstr[128];
    if(sscanf(params, "s[128]", animstr))
    {
        for(new x; x < 24; x++)
        {
            TextDrawShowForPlayer(playerid, EmotesTD[x]);
        }

        for(new x; x < 10; x++)
        {
            PlayerTextDrawSetString(playerid, EmotesPTD[playerid][x], g_AnimDetails[x][e_AnimationName]);

            PlayerTextDrawShow(playerid, EmotesPTD[playerid][x]);
        }
        animPage[playerid] = 1;

        PlayerTextDrawSetString(playerid, EmotesPTD[playerid][10], sprintf("%02d / %02d", animPage[playerid], sizeof(g_AnimDetails)/10 + 1));
        PlayerTextDrawShow(playerid, EmotesPTD[playerid][10]);
        SelectTextDraw(playerid, 0xff91a4cc);
        return 1;
    }

    if(!strcmp("x", animstr, true))
    {
        gPlayerUsingLoopingAnim[playerid] = false;
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, 9);
        return StopRunningAnimation(playerid);
    }
    
    else if(!strcmp("Kencing", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        return SetPlayerSpecialAction(playerid, 68);
    }
    else if(!strcmp("Angtang2", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_HANDSUP);
    }
    else if(!strcmp("Dansa", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE1);
    }
    else if(!strcmp("Dansa2", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE2);
    }
    else if(!strcmp("Dansa3", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE3);
    }
    else if(!strcmp("Dansa4", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE4);
    }
    else if(!strcmp("Carry", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    }

    GetListAnimName(playerid, animstr);
    return 1;
}

YCMD:eprop(playerid, params[], help)
{
    if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    if(IsPlayerStunned(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    if(AccountData[playerid][pInEvent]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    if(pPorterCarrying[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");

    static animstr[128];
    if(sscanf(params, "s[128]", animstr)) return SUM(playerid, "/eprop [nama animasi]");

    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    RemovePlayerAttachedObject(playerid, 9);
    StopRunningAnimation(playerid);
    
    if(!strcmp("Box", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        SetPlayerAttachedObject(playerid, 9, 1271, 5, 0.094000, 0.164999, 0.164000, 6.700001, 15.199984, 8.599995, 0.592999, 0.513999, 0.592000, 0, 0);
        return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    }
    else if(!strcmp("Box2", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        SetPlayerAttachedObject(playerid, 9, 2814, 1, 0.083000, 0.297000, -0.029000, -91.200042, 32.800014, 0.000000, 1.000000, 1.000000, 1.000000, 0, 0);
        return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    }
    else if(!strcmp("Box3", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        SetPlayerAttachedObject(playerid, 9, 19638, 1, -0.000000, 0.527000, -0.018999, 87.099983, 87.599990, 0.000000, 1.000000, 1.000000, 1.853998, 0, 0);
        return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    }
    else if(!strcmp("Ban", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        SetPlayerAttachedObject(playerid, 9, 1096, 6, 0.046000, 0.183000, -0.197999, 0.000000, -4.899998, 10.800001, 0.703000, 0.579000, 0.548999);
        return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    }
    else if(!strcmp("Bumper", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        SetPlayerAttachedObject(playerid, 9, 1159, 6, 0.423999, 0.407999, -1.410999, -31.499994, 80.799987, 12.599996, 1.000000, 1.000000, 1.000000);
        return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    }
    else if(!strcmp("Bumper2", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        SetPlayerAttachedObject(playerid, 9, 1185, 6, 0.268999, -0.135999, -1.133999, 0.000000, 84.800003, -15.300001, 1.000000, 1.000000, 1.000000);
        return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    }
    else if(!strcmp("Toolbox", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        SetPlayerAttachedObject(playerid, 9, 19921, 6, 0.064000, 0.028000, 0.009999, 102.400039, 0.000000, -94.300010, 1.000000, 1.000000, 1.000000);
        return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    }
    else if(!strcmp("Koper", animstr, true)) 
    {
        gPlayerUsingLoopingAnim[playerid] = true;
        SetPlayerAttachedObject(playerid, 9, 19624, 6, 0.061000, 0.012000, 0.000000, 0.000000, -100.799995, 0.000000, 1.000000, 1.000000, 1.000000);
        return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    }

    GetListPropAnimName(playerid, animstr);
    return 1;
}

YCMD:eshared(playerid, params[], help)
{
    if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    if(IsPlayerStunned(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    if(AccountData[playerid][pInEvent]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    if(pPorterCarrying[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");

    static otherid, animstr[128];
    if(sscanf(params, "ds[128]", otherid, animstr)) return SUM(playerid, "/eshared [playerid] [nama animasi]");

    if(otherid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya terhadap diri sendiri!");
    if(!IsPlayerConnected(otherid) && !AccountData[otherid][pSpawned]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn/tidak terkoneksi ke server!");

    if(!IsPlayerNearPlayer(playerid, otherid, 2.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Pemain tersebut!");
    if(pPorterCarrying[otherid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang sibuk!");

    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    RemovePlayerAttachedObject(playerid, 9);
    StopRunningAnimation(playerid);

    SetPlayerSpecialAction(otherid, SPECIAL_ACTION_NONE);
    RemovePlayerAttachedObject(otherid, 9);
    StopRunningAnimation(otherid);

    if(!strcmp("Cipok", animstr, true)) 
    {
        AccountData[otherid][pESharedType] = 1;
        AccountData[otherid][pESharedOfferer] = playerid;
        SendClientMessageEx(otherid, Y_SERVER, "(Emote Shared) "RED"%s (%d) "WHITE"request "ORANGE"'%s' "WHITE"to you, use "CMDEA"'/accept eshared' "WHITE"to proceed.", AccountData[playerid][pName], playerid, animstr);
    }

    else if(!strcmp("Cipok2", animstr, true)) 
    {
        AccountData[otherid][pESharedType] = 2;
        AccountData[otherid][pESharedOfferer] = playerid;

        SendClientMessageEx(otherid, Y_SERVER, "(Emote Shared) "RED"%s (%d) "WHITE"request "ORANGE"'%s' "WHITE"to you, use "CMDEA"'/accept eshared' "WHITE"to proceed.", AccountData[playerid][pName], playerid, animstr);
    }
    else if(!strcmp("Cipok3", animstr, true)) 
    {
        AccountData[otherid][pESharedType] = 3;
        AccountData[otherid][pESharedOfferer] = playerid;
        SendClientMessageEx(otherid, Y_SERVER, "(Emote Shared) "RED"%s (%d) "WHITE"request "ORANGE"'%s' "WHITE"to you, use "CMDEA"'/accept eshared' "WHITE"to proceed.", AccountData[playerid][pName], playerid, animstr);
    }
    else if(!strcmp("Gift", animstr, true)) 
    {
        AccountData[otherid][pESharedType] = 4;
        AccountData[otherid][pESharedOfferer] = playerid;
        SendClientMessageEx(otherid, Y_SERVER, "(Emote Shared) "RED"%s (%d) "WHITE"request "ORANGE"'%s' "WHITE"to you, use "CMDEA"'/accept eshared' "WHITE"to proceed.", AccountData[playerid][pName], playerid, animstr);
    }
    else if(!strcmp("Nikmat", animstr, true)) 
    {
        AccountData[otherid][pESharedType] = 5;
        AccountData[otherid][pESharedOfferer] = playerid;
        SendClientMessageEx(otherid, Y_SERVER, "(Emote Shared) "RED"%s (%d) "WHITE"request "ORANGE"'%s' "WHITE"to you, use "CMDEA"'/accept eshared' "WHITE"to proceed.", AccountData[playerid][pName], playerid, animstr);
    }
    else if(!strcmp("Nikmat2", animstr, true)) 
    {
        AccountData[otherid][pESharedType] = 6;
        AccountData[otherid][pESharedOfferer] = playerid;
        SendClientMessageEx(otherid, Y_SERVER, "(Emote Shared) "RED"%s (%d) "WHITE"request "ORANGE"'%s' "WHITE"to you, use "CMDEA"'/accept eshared' "WHITE"to proceed.", AccountData[playerid][pName], playerid, animstr);
    }
    else if(!strcmp("Salam", animstr, true)) 
    {
        AccountData[otherid][pESharedType] = 7;
        AccountData[otherid][pESharedOfferer] = playerid;
        SendClientMessageEx(otherid, Y_SERVER, "(Emote Shared) "RED"%s (%d) "WHITE"request "ORANGE"'%s' "WHITE"to you, use "CMDEA"'/accept eshared' "WHITE"to proceed.", AccountData[playerid][pName], playerid, animstr);
    }
    else if(!strcmp("Salam2", animstr, true)) 
    {
        AccountData[otherid][pESharedType] = 8;
        AccountData[otherid][pESharedOfferer] = playerid;
        SendClientMessageEx(otherid, Y_SERVER, "(Emote Shared) "RED"%s (%d) "WHITE"request "ORANGE"'%s' "WHITE"to you, use "CMDEA"'/accept eshared' "WHITE"to proceed.", AccountData[playerid][pName], playerid, animstr);
    }
    else if(!strcmp("Salam3", animstr, true)) 
    {
        AccountData[otherid][pESharedType] = 9;
        AccountData[otherid][pESharedOfferer] = playerid;
        SendClientMessageEx(otherid, Y_SERVER, "(Emote Shared) "RED"%s (%d) "WHITE"request "ORANGE"'%s' "WHITE"to you, use "CMDEA"'/accept eshared' "WHITE"to proceed.", AccountData[playerid][pName], playerid, animstr);
    }
    else if(!strcmp("Salam4", animstr, true)) 
    {
        AccountData[otherid][pESharedType] = 10;
        AccountData[otherid][pESharedOfferer] = playerid;
        SendClientMessageEx(otherid, Y_SERVER, "(Emote Shared) "RED"%s (%d) "WHITE"request "ORANGE"'%s' "WHITE"to you, use "CMDEA"'/accept eshared' "WHITE"to proceed.", AccountData[playerid][pName], playerid, animstr);
    }
    else if(!strcmp("Salam5", animstr, true)) 
    {
        AccountData[otherid][pESharedType] = 11;
        AccountData[otherid][pESharedOfferer] = playerid;
        SendClientMessageEx(otherid, Y_SERVER, "(Emote Shared) "RED"%s (%d) "WHITE"request "ORANGE"'%s' "WHITE"to you, use "CMDEA"'/accept eshared' "WHITE"to proceed.", AccountData[playerid][pName], playerid, animstr);
    }
    else if(!strcmp("Salam6", animstr, true)) 
    {
        AccountData[otherid][pESharedType] = 12;
        AccountData[otherid][pESharedOfferer] = playerid;
        SendClientMessageEx(otherid, Y_SERVER, "(Emote Shared) "RED"%s (%d) "WHITE"request "ORANGE"'%s' "WHITE"to you, use "CMDEA"'/accept eshared' "WHITE"to proceed.", AccountData[playerid][pName], playerid, animstr);
    }
    else if(!strcmp("Salam7", animstr, true)) 
    {
        AccountData[otherid][pESharedType] = 13;
        AccountData[otherid][pESharedOfferer] = playerid;
        SendClientMessageEx(otherid, Y_SERVER, "(Emote Shared) "RED"%s (%d) "WHITE"request "ORANGE"'%s' "WHITE"to you, use "CMDEA"'/accept eshared' "WHITE"to proceed.", AccountData[playerid][pName], playerid, animstr);
    }
    else
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Shared emote tersebut tidak terdaftar!");
    }
    ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengirimkan permohonan emote shared, harap tunggu.");
    return 1;
}

YCMD:elist(playerid, params[], help)
{
    Dialog_Show(playerid, "EmoteList", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Daftar Emote", "Emotes\n"GRAY"Emotes Property\nEmotes Shared", "Pilih", "Batal");
	return 1;
}
