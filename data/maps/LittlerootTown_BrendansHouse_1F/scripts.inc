.set LOCALID_MOM, 1
.set LOCALID_RIVAL_MOM, 4
.set LOCALID_RIVAL, 7

LittlerootTown_BrendansHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, LittlerootTown_BrendansHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_BrendansHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_BrendansHouse_1F_OnFrame
	.byte 0

LittlerootTown_BrendansHouse_1F_OnLoad:
	call_if_lt VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes
	call_if_set FLAG_RECEIVED_RUNNING_SHOES, LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual
	end

LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes::
	setmetatile 5, 4, METATILE_BrendansMaysHouse_MovingBox_Open, TRUE
	setmetatile 5, 2, METATILE_BrendansMaysHouse_MovingBox_Closed, TRUE
	return

LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual
	return

LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual::
	setmetatile 3, 7, METATILE_BrendansMaysHouse_BookOnTable, TRUE
	return

LittlerootTown_BrendansHouse_1F_OnTransition:
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV
	end

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs::
	setobjectxyperm LOCALID_MOM, 8, 4
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV::
	setobjectxyperm LOCALID_MOM, 4, 5
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor::
	setobjectxyperm LOCALID_MOM, 9, 8
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

@ Many of the below scripts have no gender check because they assume youre in the correct house
@ The below SS Ticket script uses Mays house state by accident(?), but theyre both set identically after the intro
LittlerootTown_BrendansHouse_1F_OnFrame:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 1, LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 3, PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV
	.2byte 0

LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock::
	lockall
	msgbox PlayersHouse_1F_Text_GoSetTheClock, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	applymovement LOCALID_MOM, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	waitmovement 0
	warp MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F, 7, 1
	waitstate
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs:
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn::
	lockall
	setvar VAR_0x8004, LOCALID_MOM
	setvar VAR_0x8005, MALE
	goto PlayersHouse_1F_EventScript_EnterHouseMovingIn
	end

LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport::
	lockall
	setvar VAR_0x8004, MALE
	setvar VAR_0x8005, LOCALID_MOM
	goto PlayersHouse_1F_EventScript_PetalburgGymReportMale
	end

LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor::
	lockall
	playse SE_PIN
	applymovement LOCALID_RIVAL_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL_MOM, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_RIVAL_MOM, LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach
	waitmovement 0
	special GetRivalSonDaughterString
	msgbox RivalsHouse_1F_Text_OhYoureTheNewNeighbor, MSGBOX_DEFAULT
	setflag FLAG_MET_RIVAL_MOM
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 2
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_GoSeeRoom::
	lockall
	setvar VAR_0x8004, LOCALID_MOM
	setvar VAR_0x8005, MALE
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto PlayersHouse_1F_EventScript_MomGoSeeRoom
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival0::
	lockall
	setvar VAR_0x8008, 0
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival1::
	lockall
	setvar VAR_0x8008, 1
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival2::
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival::
	playse SE_EXIT
	delay 10
	addobject LOCALID_RIVAL
	delay 30
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call_if_ne VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2
	msgbox RivalsHouse_1F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2
	playse SE_EXIT
	removeobject LOCALID_RIVAL
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_BRENDAN
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	delay 30
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1:
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0::
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1::
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2::
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1:
	delay_16
	delay_8
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

PlayersHouse_1F_Text_IsntItNiceInHere:
	.string "ΜΑΜΑ: Βλέπεις, {PLAYER};\n"
	.string "Δεν είναι κι εδώ ωραία;$"

PlayersHouse_1F_Text_MoversPokemonGoSetClock:
	.string "Τα POKéMON της μεταφορικής κάνουν\n"
	.string "όλη τη δουλειά, και μετά καθαρίζουν.\l"
	.string "Είναι τόσο βολικό!\p"
	.string "{PLAYER}, το δωμάτιό σου είναι πάνω.\n"
	.string "Ρίξε μια ματιά, αγάπη μου!\p"
	.string "Ο ΜΠΑΜΠΑΣ σου αγόρασε ένα ρολόι\n"
	.string "σαν ενθύμιο της μετακόμισής μας.\l"
	.string "Μην ξεχάσεις να το ρυθμίσεις!$"

PlayersHouse_1F_Text_ArentYouInterestedInRoom:
	.string "ΜΑΜΑ: Λοιπόν, {PLAYER};\p"
	.string "Δεν σε ενδιαφέρει να δεις\n"
	.string "το δωμάτιό σου;$"

PlayersHouse_1F_Text_GoSetTheClock:
	.string "ΜΑΜΑ: {PLAYER}.\p"
	.string "Πήγαινε ρύθμισε το ρολόι\n"
	.string "στο δωμάτιό σου, {HONEY} μου.$"

PlayersHouse_1F_Text_OhComeQuickly:
	.string "ΜΑΜΑ: Ω! {PLAYER}, {PLAYER}!\n"
	.string "Βιάσου! Έλα γρήγορα!$"

PlayersHouse_1F_Text_MaybeDadWillBeOn:
	.string "ΜΑΜΑ: Κοίτα! Είναι το ΓΥΜΝΑΣΤΗΡΙΟ PETALBURG!\n"
	.string "Ίσως δείξουν τον ΜΠΑΜΠΑ!$"

PlayersHouse_1F_Text_ItsOverWeMissedHim:
	.string "ΜΑΜΑ: Ω… Τελείωσε.\p"
	.string "Νομίζω έδειξαν τον μπαμπά, αλλά τον\n"
	.string "χάσαμε. Κρίμα.$"

PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor:
	.string "Ω, ναι.\n"
	.string "Ένας φίλος του ΜΠΑΜΠΑ μένει στην πόλη.\p"
	.string "Τον λένε ΚΑΘ. BIRCH.\p"
	.string "Μένει ακριβώς δίπλα, οπότε πήγαινε\n"
	.string "μέχρι εκεί και συστήσου.$"

PlayersHouse_1F_Text_SeeYouHoney:
	.string "ΜΑΜΑ: Τα λέμε, {HONEY} μου!$"

PlayersHouse_1F_Text_DidYouMeetProfBirch:
	.string "ΜΑΜΑ: Πήγες να συστηθείς στον\n"
	.string "ΚΑΘ. BIRCH;$"

PlayersHouse_1F_Text_YouShouldRestABit:
	.string "ΜΑΜΑ: Πως είσαι, {PLAYER};\n"
	.string "Φαίνεσαι λίγο κουρασμέν{PLAYER_ADJ}.\p"
	.string "Καλύτερα να ξεκουραστείς λιγάκι.$"

PlayersHouse_1F_Text_TakeCareHoney:
	.string "ΜΑΜΑ: Να προσέχεις, {HONEY} μου!$"

PlayersHouse_1F_Text_GotDadsBadgeHeresSomethingFromMom:
	.string "ΜΑΜΑ: Ω; Ο ΜΠΑΜΠΑΣ σου έδωσε αυτό το ΕΜΒΛΗΜΑ;\p"
	.string "Τότε ορίστε και κάτι από τη ΜΑΜΑ σου!$"

PlayersHouse_1F_Text_DontPushYourselfTooHard:
	.string "Μην πιέζεις τον εαυτό σου υπερβολικά,\n"
	.string "αγάπη μου. Μπορείς πάντα να έρχεσαι σπίτι.\p"
	.string "Βάλε τα δυνατά σου, {HONEY} μου!$"

PlayersHouse_1F_Text_IsThatAPokenav:
	.string "ΜΑΜΑ: Τι είναι αυτό, {HONEY} μου; Ένα POKéNAV;\n"
	.string "Σου το έδωσε κάποιος από την DEVON;\p"
	.string "Λοιπόν, {HONEY} μου, γιατί δεν\n"
	.string "γράφεις και τη μαμά σου;\p"
	.string "… … …$"

PlayersHouse_1F_Text_RegisteredMom:
	.string "Η ΜΑΜΑ εγγράφηκε\n"
	.string "στο POKéNAV.$"

PlayersHouse_1F_Text_Vigoroth1:
	.string "Φουγκίιιιι!$"

PlayersHouse_1F_Text_Vigoroth2:
	.string "Χουγκό, ουγκό ουγκό…$"

PlayersHouse_1F_Text_ReportFromPetalburgGym:
	.string "ΔΗΜΟΣΙΟΓΡΑΦΟΣ: …Σας φέραμε αυτό το\n"
	.string "ρεπορτάζ μπροστά από το ΓΥΜΝΑΣΤΗΡΙΟ PETALBURG.$"

PlayersHouse_1F_Text_TheresAMovieOnTV:
	.string "Παίζει μια ταινία στην τηλεόραση.\p"
	.string "Δύο άντρες χορεύουν πάνω σε ένα\n"
	.string "τεράστιο πιάνο.\p"
	.string "Καλύτερα να πηγαίνω!$"

PlayersHouse_1F_Text_RunningShoesManual:
	.string "Είναι το εγχειρίδιο για τα\n"
	.string "ΑΘΛΗΤΙΚΑ ΠΑΠΟΥΤΣΙΑ.\p"
	.string "“Πίεσε το Πλήκτρο B για να τρέξεις\n"
	.string "ενώ φοράς τα ΑΘΛΗΤΙΚΑ ΠΑΠΟΥΤΣΙΑ.\p"
	.string "“Δέσε τα ΑΘΛΗΤΙΚΑ ΠΑΠΟΥΤΣΙΑ και\n"
	.string "πάρε το δρόμο τρέχοντας!”$"

PlayersHouse_1F_Text_TicketFromBrineyCameForYou:
	.string "ΜΠΑΜΠΑΣ: Χμ;\p"
	.string "Ω, είναι {PLAYER_ART_LOWER} {PLAYER}!\p"
	.string "Έχω πολύ καιρό να σε δω, αλλά μου\n"
	.string "φαίνεσαι…δυνατότερ{PLAYER_ADJ}, κάπως.\p"
	.string "Αυτή την εντύπωση μου δίνεις.\n"
	.string "Αλλά δεν τα παρατά ακόμα ο γέρος σου!\p"
	.string "Α, ναι, έχω κάτι εδώ για σένα.\n"
	.string "Αυτό ήρθε από κάποιον που λέγεται\l"
	.string "ΚΟΣ. BRINEY.$"

PlayersHouse_1F_Text_PortsInSlateportLilycove:
	.string "ΜΠΑΜΠΑΣ: Χμ, ένα ΕΙΣΙΤΗΡΙΟ για φέρι μποτ;\p"
	.string "Αν θυμάμαι σωστά, υπάρχει λιμάνι\n"
	.string "στη SLATEPORT και στη LILYCOVE.$"

PlayersHouse_1F_Text_BetterGetBackToGym:
	.string "Καλύτερα να πηγαίνω πίσω στο\n"
    .string	"ΓΥΜΝΑΣΤΗΡΙΟ PETALBURG.\p"
	.string "ΜΑΜΑ, σ' ευχαριστώ που προσέχεις\n"
	.string "το σπίτι όσο λείπω.$"

PlayersHouse_1F_Text_DadShouldStayLonger:
	.string "ΜΑΜΑ: Αυτός ο ΜΠΑΜΠΑΣ σου…\p"
	.string "Έρχεται σπίτι για πρώτη φορά εδώ και\n"
	.string "καιρό, και μόνο για POKéMON μιλάει.\p"
	.string "Πρέπει να χαλαρώσει και να μείνει\n"
	.string "σπίτι για λιγάκι.$"

PlayersHouse_1F_Text_IsThatABreakingStory:
	.string "ΜΑΜΑ: Παίζει έκτακτο δελτίο;$"

PlayersHouse_1F_Text_LatiEmergencyNewsFlash:
	.string "Διακόπτουμε το πρόγραμμά μας για\n"
	.string "μία έκτακτη είδηση!\p"
	.string "Σε διάφορα τοπία της HOENN, υπάρχουν\n"
	.string "υπάρχουν αναφορές ενός ιπτάμενου\l"
	.string "POKéMON με ΜΠΖΖΤ…χρώμα.\p"
	.string "Η ταυτότητα του POKéMON είναι\n"
	.string "αυτή τη στιγμή άγνωστη.\p"
	.string "Επιστρέφουμε τώρα στο\n"
	.string "κανονικό μας πρόγραμμα..$"

PlayersHouse_1F_Text_WhatColorDidTheySay:
	.string "ΜΑΜΑ: {PLAYER}, το έπιασες αυτό;\p"
	.string "Τι χρώμα είπε ο δημοσιογράφος πως\n"
	.string "είχε το POKéMON;$"

PlayersHouse_1F_Text_StillUnknownPokemon:
	.string "ΜΑΜΑ: Λοιπόν, αυτό ήταν το κάτι άλλο!\n"
	.string "Υπάρχουν ακόμα άγνωστα POKéMON.$"
