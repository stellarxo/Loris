DROP TABLE IF EXISTS mullen_composite_lookup;

CREATE TABLE `mullen_composite_lookup` (
                 	`cognitive_t_sum` int(3) NOT NULL,
			`composite_standard_score` int(3) NOT NULL,
			`percentile` int(2) NOT NULL
              ) TYPE=MyISAM;


INSERT INTO mullen_composite_lookup VALUES
(320, 155, 99),
(319, 155, 99),
(318, 154, 99),
(317, 154, 99),
(316, 154, 99),
(315, 153, 99),
(314, 153, 99),
(313, 153, 99),
(312, 152, 99),
(311, 152, 99),
(310, 151, 99),
(309, 151, 99),
(308, 151, 99),
(307, 150, 99),
(306, 150, 99),
(305, 149, 99),
(304, 149, 99),
(303, 149, 99),
(302, 148, 99),
(301, 148, 99),
(300, 147, 99),
(299, 147, 99),
(298, 147, 99),
(297, 146, 99),
(296, 146, 99),
(295, 145, 99),
(294, 145, 99),
(293, 144, 99),
(292, 144, 99),
(291, 144, 99),
(290, 143, 99),
(289, 143, 99),
(288, 142, 99),
(287, 142, 99),
(286, 141, 99),
(285, 141, 99),
(284, 141, 99),
(283, 140, 99),
(282, 140, 99),
(281, 139, 99),
(280, 139, 99),
(279, 138, 99),
(278, 138, 99),
(277, 137, 99),
(276, 137, 99),
(275, 137, 99),
(274, 136, 99),
(273, 136, 99),
(272, 135, 99),
(271, 135, 99),
(270, 134, 99),
(269, 134, 99),
(268, 133, 99),
(267, 133, 99),
(266, 132, 98),
(265, 132, 98),
(264, 131, 98),
(263, 131, 98),
(262, 130, 98),
(261, 130, 98),
(260, 129, 98),
(259, 129, 97),
(258, 129, 97),
(257, 128, 97),
(256, 128, 97),
(255, 127, 97),
(254, 127, 96),
(253, 126, 96),
(252, 126, 96),
(251, 125, 95),
(250, 125, 95),
(249, 124, 95),
(248, 124, 94),
(247, 123, 94),
(246, 123, 94),
(245, 122, 93),
(244, 122, 93),
(243, 122, 92),
(242, 121, 92),
(241, 121, 91),
(240, 120, 91),
(239, 120, 90),
(238, 119, 90),
(237, 119, 89),
(236, 118, 89),
(235, 118, 88),
(234, 117, 87),
(233, 117, 87),
(232, 116, 86),
(231, 116, 85),
(230, 115, 84),
(229, 115, 83),
(228, 114, 83),
(227, 114, 82),
(226, 113, 81),
(225, 113, 80),
(224, 112, 79),
(223, 112, 78),
(222, 111, 77),
(221, 111, 76),
(220, 110, 75),
(219, 110, 74),
(218, 109, 73),
(217, 109, 72),
(216, 108, 70),
(215, 108, 69),
(214, 107, 68),
(213, 107, 67),
(212, 106, 66),
(211, 106, 64),
(210, 105, 63),
(209, 105, 62),
(208, 104, 61),
(207, 104, 59),
(206, 103, 58),
(205, 102, 57),
(204, 102, 55),
(203, 101, 54),
(202, 101, 53),
(201, 100, 51),
(200, 100, 50),
(199, 99, 49),
(198, 99, 47),
(197, 98, 46),
(196, 98, 45),
(195, 97, 43),
(194, 97, 42),
(193, 96, 41),
(192, 96, 39),
(191, 95, 38),
(190, 95, 37),
(189, 95, 36),
(188, 94, 34),
(187, 94, 33),
(186, 93, 32),
(185, 93, 31),
(184, 92, 30),
(183, 92, 29),
(182, 91, 28),
(181, 91, 27),
(180, 90, 25),
(179, 90, 24),
(178, 89, 23),
(177, 89, 22),
(176, 88, 21),
(175, 88, 21),
(174, 87, 20),
(173, 87, 19),
(172, 86, 18),
(171, 86, 17),
(170, 85, 16),
(169, 85, 16),
(168, 84, 15),
(167, 84, 14),
(166, 83, 13),
(165, 83, 13),
(164, 82, 12),
(163, 82, 12),
(162, 82, 11),
(161, 81, 10),
(160, 81, 10),
(159, 80, 9),
(158, 80, 9),
(157, 79, 8),
(156, 79, 8),
(155, 78, 7),
(154, 78, 7),
(153, 77, 7),
(152, 77, 6),
(151, 77, 6),
(150, 76, 6),
(149, 76, 5),
(148, 75, 5),
(147, 75, 5),
(146, 74, 4),
(145, 74, 4),
(144, 73, 4),
(143, 73, 4),
(142, 73, 3),
(141, 72, 3),
(140, 72, 3),
(139, 71, 3),
(138, 71, 3),
(137, 70, 2),
(136, 70, 2),
(135, 70, 2),
(134, 69, 2),
(133, 69, 2),
(132, 68, 2),
(131, 68, 2),
(130, 67, 1),
(129, 67, 1),
(128, 67, 1),
(127, 66, 1),
(126, 66, 1),
(125, 65, 1),
(124, 65, 1),
(123, 65, 1),
(122, 64, 1),
(121, 64, 1),
(120, 63, 1),
(119, 63, 1),
(118, 63, 1),
(117, 62, 1),
(116, 62, 1),
(115, 61, 1),
(114, 61, 1),
(113, 61, 1),
(112, 60, 1),
(111, 60, 1),
(110, 59, 1),
(109, 59, 1),
(108, 59, 1),
(107, 58, 1),
(106, 58, 1),
(105, 58, 1),
(104, 57, 1),
(103, 57, 1),
(102, 56, 1),
(101, 56, 1),
(100, 56, 1),
(99, 55, 1),
(98, 55, 1),
(97, 55, 1),
(96, 54, 1),
(95, 54, 1),
(94, 54, 1),
(93, 53, 1),
(92, 53, 1),
(91, 52, 1),
(90, 52, 1),
(89, 52, 1),
(88, 51, 1),
(87, 51, 1),
(86, 51, 1),
(85, 50, 1),
(84, 50, 1),
(83, 50, 1),
(82, 49, 1),
(81, 49, 1),
(80, 49, 1);
