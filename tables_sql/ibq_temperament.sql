CREATE TABLE `ibq_temperament` (
`CommentID` varchar(255) NOT NULL default '',

                          `UserID` varchar(255) default NULL,

                          `Examiner` varchar(255) default NULL,

                          `Testdate` timestamp(14) NOT NULL,

                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`activity_level` varchar(255) default NULL,
`distress_to_limitations` varchar(255) default NULL,
`fear` varchar(255) default NULL,
`duration_of_orienting` varchar(255) default NULL,
`smiling_and_laughter` varchar(255) default NULL,
`high_pleasure` varchar(255) default NULL,
`low_pleasure` varchar(255) default NULL,
`soothability` varchar(255) default NULL,
`falling_reactivity` varchar(255) default NULL,
`cuddliness` varchar(255) default NULL,
`perceptual_sensitivity` varchar(255) default NULL,
`sadness` varchar(255) default NULL,
`approach` varchar(255) default NULL,
`vocal_reactivity` varchar(255) default NULL,
`q_1` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_2` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_3` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_4` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_5` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_6` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_7` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_8` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_9` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_10` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_11` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_12` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_13` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_14` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_15` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_16` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_17` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_18` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_19` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_20` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_21` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_22` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_23` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_24` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_25` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_26` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_27` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_28` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_29` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_30` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_31` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_32` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_33` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_34` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_35` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_36` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_37` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_38` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_39` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_40` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_41` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_42` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_43` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_44` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_45` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_46` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_47` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_48` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_49` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_50` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_51` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_52` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_53` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_54` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_55` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_56` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_57` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_58` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_59` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_60` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_61` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_62` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_63` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_64` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_65` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_66` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_67` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_68` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_69` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_70` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_71` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_72` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_73` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_74` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_75` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_76` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_77` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_78` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_79` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_80` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_81` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_82` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_83` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_84` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_85` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_86` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_87` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_88` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_89` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_90` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_91` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_92` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_93` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_94` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_95` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_96` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_97` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_98` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_99` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_100` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_101` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_102` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_103` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_104` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_105` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_106` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_107` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_108` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_109` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_110` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_111` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_112` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_113` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_114` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_115` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_116` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_117` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_118` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_119` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_120` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_121` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_122` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_123` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_124` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_125` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_126` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_127` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_128` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_129` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_130` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_131` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_132` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_133` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_134` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_135` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_136` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_137` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_138` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_139` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_140` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_141` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_142` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_143` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_144` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_145` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_146` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_147` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_148` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_149` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_150` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_151` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_152` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_153` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_154` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_155` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_156` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_157` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_158` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_159` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_160` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_161` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_162` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_163` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_164` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_165` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_166` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_167` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_168` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_169` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_170` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_171` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_172` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_173` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_174` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_175` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_176` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_177` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_178` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_179` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_180` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_181` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_182` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_183` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_184` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_185` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_186` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_187` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_188` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_189` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_190` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
`q_191` enum('1','2','3','4','5','6','7','does_not_apply','not_answered') default NULL,
PRIMARY KEY  (`CommentID`)

              ) TYPE=MyISAM;