CREATE TABLE `m_chat` (
`CommentID` varchar(255) NOT NULL default '',

                          `UserID` varchar(255) default NULL,

                          `Examiner` varchar(255) default NULL,

                          `Testdate` timestamp(14) NOT NULL,

                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`item_fails` varchar(255) default NULL,
`critical_fails` varchar(255) default NULL,
`score` varchar(255) default NULL,
`1_swung_on_knee` enum('yes','no','not_answered') default NULL,
`2_interest_other_children` enum('yes','no','not_answered') default NULL,
`3_climbing` enum('yes','no','not_answered') default NULL,
`4_peek_a_boo` enum('yes','no','not_answered') default NULL,
`5_pretends` enum('yes','no','not_answered') default NULL,
`6_index_point` enum('yes','no','not_answered') default NULL,
`7_index_interest` enum('yes','no','not_answered') default NULL,
`8_play_properly` enum('yes','no','not_answered') default NULL,
`9_bring_objects` enum('yes','no','not_answered') default NULL,
`10_look_eye` enum('yes','no','not_answered') default NULL,
`11_oversensitive` enum('yes','no','not_answered') default NULL,
`12_smile_to_face` enum('yes','no','not_answered') default NULL,
`13_imitate_you` enum('yes','no','not_answered') default NULL,
`14_respond_to_name` enum('yes','no','not_answered') default NULL,
`15_point_and_look` enum('yes','no','not_answered') default NULL,
`16_walk` enum('yes','no','not_answered') default NULL,
`17_look_at_similar` enum('yes','no','not_answered') default NULL,
`18_unusual_finger` enum('yes','no','not_answered') default NULL,
`19_try_to_attract` enum('yes','no','not_answered') default NULL,
`20_wondered_deaf` enum('yes','no','not_answered') default NULL,
`21_understand_speach` enum('yes','no','not_answered') default NULL,
`22_stare_no_purpose` enum('yes','no','not_answered') default NULL,
`23_look_at_face` enum('yes','no','not_answered') default NULL,
PRIMARY KEY  (`CommentID`)

              ) TYPE=MyISAM;
