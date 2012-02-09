#include "bnk_pc.h"

u16 char_tbl_sk[4096] = {
0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
32,   33,   34,   35,   36,   37,   38,   39,   40,   41,   42,   43,   44,   45,   46,   47,
48,   49,   50,   51,   52,   53,   54,   55,   56,   57,   58,   59,   60,   61,   62,   63,
64,   65,   66,   67,   68,   69,   70,   71,   72,   73,   74,   75,   76,   77,   78,   79,
80,   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,   91,   92,   93,   94,   95,
96,   97,   98,   99,   100,  101,  102,  103,  104,  105,  106,  107,  108,  109,  110,  111,
112,  113,  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,  124,  125,  126,  0,
0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
160,  161,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
176,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    191,
192,  193,  194,  0,    196,  0,    198,  199,  200,  201,  202,  203,  204,  205,  206,  207,
0,    209,  210,  211,  212,  0,    214,  0,    0,    217,  218,  219,  220,  221,  0,    223,
224,  225,  226,  0,    228,  0,    230,  231,  232,  233,  234,  235,  236,  237,  238,  239,
0,    241,  242,  243,  244,  0,    246,  0,    0,    249,  250,  251,  252,  253,    0,    0,
260,  262,  268,  270,  280,  282,  321,  323,  327,  338,  344,  346,  352,  356,  366,  377,
379,  381,  1025, 1040, 1041, 1042, 1043, 1044, 1045, 1046, 1047, 1048, 1049, 1050, 1051, 1052,
1053, 1054, 1055, 1056, 1057, 1058, 1059, 1060, 1061, 1062, 1063, 1064, 1065, 1066, 1067, 1068,
1069, 1070, 1071, 8211, 8216, 8217, 8218, 8220, 8221, 8222, 8230, 8364, 8482, 44032,44033,44036,
44040,44048,44049,44050,44052,44053,44054,44057,44060,44061,44079,44081,44144,44148,44151,44152,
44160,44161,44163,44169,44170,44172,44176,44192,44200,44201,44204,44208,44220,44221,44228,44256,
44257,44260,44263,44264,44275,44277,44284,44288,44305,44340,44368,44396,44397,44400,44404,44405,
44412,44413,44428,44480,44499,44512,44536,44537,44540,44544,44552,44553,44592,44596,44600,44608,
44609,44611,44618,44620,44636,44637,44645,44648,44732,44751,44760,44844,44867,44873,44893,44900,
44984,44988,44992,44999,45000,45001,45033,45068,45076,45124,45128,45130,45132,45140,45149,45180,
45208,45209,45212,45216,45217,45224,45225,45228,45229,45230,45236,45240,45244,45253,45256,45257,
45264,45285,45320,45324,45328,45336,45347,45348,45349,45367,45376,45380,45392,45400,45432,45433,
45440,45448,45458,45459,45516,45572,45576,45580,45589,45600,45684,45712,45716,45720,45733,45734,
45740,45768,45769,45772,45784,45785,45787,45796,45797,45800,45803,45804,45811,45812,45817,45824,
45828,45843,45908,45909,45912,45916,45924,45929,45934,45936,45937,45944,46020,46021,46024,46028,
46041,46076,46096,46104,46108,46112,46120,46121,46160,46161,46168,46177,46244,46263,46272,46300,
46301,46304,46307,46308,46317,46321,46356,46364,46377,46378,46384,46412,46496,46500,46504,46524,
46540,46608,46749,46769,46832,46888,46907,46944,46972,46973,46976,46988,46989,46992,46993,47000,
47001,47004,47008,47017,47019,47021,47029,47049,47084,47085,47088,47100,47101,47104,47105,47111,
47112,47113,47116,47120,47131,47140,47141,47144,47157,47160,47161,47168,47196,47197,47200,47204,
47213,47215,47280,47308,47336,47337,47352,47448,47449,47452,47456,47464,47469,47476,47480,47484,
47492,47493,47502,47532,47533,47536,47540,47548,47549,47551,47553,47560,47561,47564,47566,47568,
47569,47581,47582,47588,47589,47592,47605,47672,47673,47676,47680,47688,47691,47693,47700,47708,
47719,47728,47732,47749,47751,47784,47785,47788,47792,47800,47803,47805,47896,47924,47926,47928,
47931,47932,47943,47956,48036,48064,48120,48121,48124,48128,48137,48141,48143,48145,48148,48149,
48150,48152,48155,48156,48157,48164,48165,48167,48169,48176,48177,48180,48192,48201,48260,48264,
48268,48276,48277,48279,48288,48292,48296,48307,48309,48316,48317,48320,48324,48333,48337,48372,
48373,48376,48380,48389,48393,48400,48512,48513,48516,48520,48528,48533,48537,48652,48660,48708,
48716,48725,48729,48731,48736,48737,48744,48757,48764,48784,48785,48808,48848,48904,49072,49100,
49108,49296,49324,49325,49328,49332,49340,49341,49345,49352,49353,49356,49368,49373,49380,49399,
49408,49436,49437,49438,49440,49444,49452,49453,49455,49457,49464,49465,49468,49472,49483,49492,
49496,49520,49548,49549,49552,49556,49569,49604,49632,49660,49677,49688,49692,49696,49707,49709,
49714,49716,49744,49772,49780,49800,49828,49832,49836,49844,49845,49849,49884,49885,49888,49892,
49900,49901,49905,49910,49912,49939,50024,50041,50045,50136,50416,50420,50424,50433,50472,50473,
50500,50501,50504,50505,50506,50508,50516,50517,50519,50520,50521,50526,50528,50529,50536,50545,
50549,50556,50557,50564,50567,50577,50612,50616,50619,50620,50628,50629,50630,50631,50632,50633,
50640,50644,50648,50657,50668,50669,50672,50676,50684,50685,50688,50689,50696,50724,50728,50732,
50741,50743,50752,50756,50772,50773,50780,50808,50812,50836,50837,50857,50864,50868,50872,50880,
50883,50885,50892,50896,50900,50920,50948,50949,50952,50967,50976,50977,50984,51004,51008,51012,
51020,51025,51032,51060,51061,51064,51068,51069,51075,51076,51077,51079,51080,51082,51086,51088,
51089,51092,51096,51104,51105,51109,51116,51137,51200,51201,51204,51208,51210,51216,51217,51221,
51228,51236,51256,51276,51312,51313,51316,51320,51328,51333,51339,51340,51396,51452,51453,51456,
51460,51468,51469,51473,51480,51536,51592,51593,51600,51613,51648,51649,51652,51656,51664,51665,
51667,51669,51676,51677,51687,51704,51788,51789,51901,51923,52236,52237,52264,52265,52268,52270,
52272,52280,52281,52284,52285,52286,52292,52313,52376,52377,52380,52384,52395,52397,52404,52432,
52452,52488,52509,52524,52572,52628,52629,52636,52644,52647,52649,52656,52676,52712,52768,52769,
52824,52828,52832,52840,52845,52852,52860,52880,52884,52896,52897,52964,52968,52972,52980,52983,
52992,53011,53020,53036,53040,53076,53080,53084,53092,53093,53095,53097,53132,53216,53300,53301,
53356,53360,53364,53372,53412,53416,53420,53431,53433,53440,53444,53448,53456,53457,53461,53468,
53469,53485,53489,53552,53553,53556,53560,53569,53580,53581,53584,53588,53596,53664,53668,53672,
53681,53685,53804,53888,53916,53944,53945,53948,53952,54000,54001,54004,54008,54016,54017,54021,
54028,54032,54036,54045,54047,54056,54060,54140,54144,54148,54161,54168,54172,54176,54187,54196,
54200,54204,54217,54224,54252,54253,54260,54268,54364,54392,54400,54408,54409,54413,54532,54540,
54548,54549,54588,54589,54592,54596,54609,54616,54617,54620,54624,54632,54633,54635,54637,54644,
54648,54664,54665,54693,54728,54732,54744,54749,54756,54764,54784,54788,54792,54801,54804,54805,
54840,54841,54844,54848,54856,54861,54868,54869,54872,54876,54889,54924,54925,54943,54945,54952,
54980,54988,54996,55040,55064,55072,55092,55120,55121,55124,55129,55137,55145,55148,55152,55176,
55180,55184,55192,55193,52645,44545,49512,50980,48712,46523,45460,47092,47969,45453,47925,49104,
51424,44316,47945,49789,51094,46388,46181,47579,50912,53373,50881,51500,47607,50032,44641,52841,
52632,49564,54169,46609,49689,50164,48977,48261,52293,50560,46763,45789,45143,44861,54256,52901,
44273,48197,50694,45713,54075,48709,54057,46319,48727,51219,52041,52856,44622,45776,48596,47576,
50532,54064,50964,45964,52489,49711,53441,53472,48173,45700,47212,45451,45339,52740,50277,49244,
51222,50679,45728,55080,44749,44272,55113,48391,52981,45819,51673,50865,50153,55141,52996,45544,
49240,47952,52244,53217,49899,50928,50276,54396,44845,47960,48127,45436,46164,46416,44748,45805,
51232,54984,49704,50584,44202,50687,45813,50044,12640,49360,44733,53272,52253,50476,48730,51596,
44145,52296,54536,47704,46037,47585,46980,44403,47787,46357,53748,54760,45356,48783,51608,50670,
44628,52393,55128,45480,54645,49891,49344,46385,51984,50613,46889,47609,47148,52308,49933,44058,
53680,46629,49916,47016,50444,45352,47344,52300,44417,46208,47736,52888,50143,45449,46497,45210,
44788,45321,53429,52258,44216,45188,53104,51005,47583,45252,52337,54800,47020,47577,49804,53188,
50725,44508,47610,46517,46080,44068,50997,52789,48624,54504,54915,46176,48855,54736,49116,46316,
51117,53825,52505,54981,54156,50544,51260,49371,45184,45012,44665,8595, 8600, 8594, 44555,44740,
47028,50693,53224,47128,48388,54607,48960,49940,51400,49500,51211,46392,47420,48195,51329,52392,
51908,44292,55136,48849,48184,45377,53328,45040,48923,53568,46920,44852,45565,52843,54812,46543,
54629,44452,50617,45815,48521,51693,51724,45331,50937,46372,50040,12619,50956,44285,52825,50739,
54747,45806,47353,51796,50638,48420,50734,45844,46404,45196,44624,52196,51135,50432,50572,48856,
47355,53487,49968,49480,44669,45825,46188,47364,49791,44652,44865,47129,50220,50784,46363,45823,
51144,51670,50575,45397,49989,53428,48852,51697,50144,44333,51081,44418,52252,49481,47716,48044,
45141,53037,44039,44064,44076,44116,44191,44217,44225,44361,44406,44424,44444,44557,44613,44621,
44640,44656,44704,44734,44860,44866,44901,45005,45072,45139,45227,45235,45341,45355,45396,45721,
45790,45832,45925,45927,45931,46216,46360,46400,46405,46432,46433,46516,46836,46840,46895,46896,
46916,47156,47217,47477,47495,47497,47701,47915,47971,47980,48072,48140,48159,48531,48756,48772,
48867,48868,48976,49248,49256,49334,49456,49847,49913,50025,50052,50137,50140,50184,50248,50491,
50581,50641,50661,50715,50753,50771,50924,50969,51021,51108,51172,51229,51247,51544,51674,51680,
51736,51792,51809,51844,51900,52048,52312,52423,52984,53077,53125,53459,53460,53608,53909,53960,
54029,54044,54077,54141,54157,54393,54672,54775,54785,54803,54993,55016,55028,55036,55156,51684,
46179,50740,49664,48724,50908,44752,44808,46616,48336,48869,49829,49928,50492,50745,51334,51916,
51921,54048,54605,50573,52056,45940,47159
};
