[c]	Kenbak-I Emulator
[c]	by
[c]	Mike Riley
[=]
	  The Kenbak-1 was designed by John Blankenbaker in 1970 and first sold in early
	1971.  This machine is considered to be the first "Personal Computer" according to
	the Computer History Museum.  It is interesting to note that this computer predates
	microprocessors (The Intel 4004 was released in 1971) and therefore it is built 
	entirely from simple TTL ICs.  This machine had 256 bytes of 8-bit memory implemented
	using 2 1024-bit shift registers, in essence an electronic version of the mercury
	delay lines used by EDSAC and other early computers.  The machine supports 5 different
	addressing modes, including indirect and indexed, a remarkable achivement for a 
	machine like this.  About 40 of these machines were built and sold for around $750
	each.
[=]
[h2]	Special Thanks
	I would like to thank John Blankenbaker for making this information on this machine
	readily available and for his permission to include the original programming manual
	with this emulator.
[=]
[h2]	Programming
	Refer to the including programming manual to learn how to program this interesting 
	machine.
[=]
[h2]	Assembly Language
[=]
[h1]	Opcodes
[i2]
[tb]
	| Mnemonic | Address Mode  | Hex | Octal |
	| ADD A    | Immediate     |  03 |   003 |
	|          | Memory        |  04 |   004 |
	|          | Indirect      |  05 |   005 |
	|          | Indexed       |  06 |   006 |
	|          | Ind/Indexed   |  07 |   007 |
	|          |               |     |       |
	| ADD B    | Immediate     |  43 |   103 |
	|          | Memory        |  44 |   104 |
	|          | Indirect      |  45 |   105 |
	|          | Indexed       |  46 |   106 |
	|          | Ind/Indexed   |  47 |   107 |
	|          |               |     |       |
	| ADD X    | Immediate     |  83 |   203 |
	|          | Memory        |  84 |   204 |
	|          | Indirect      |  85 |   205 |
	|          | Indexed       |  86 |   206 |
	|          | Ind/Indexed   |  87 |   207 |
	|          |               |     |       |
	| AND      | Immediate     |  D3 |   323 |
	|          | Memory        |  D4 |   324 |
	|          | Indirect      |  D5 |   325 |
	|          | Indexed       |  D6 |   326 |
	|          | Ind/Indexed   |  D7 |   327 |
	|          |               |     |       |
	| HALT     |               |  00 |   000 |
	|          |               |     |       |
	| JMD      | Unconditional |  F3 |   363 |
	|          |               |     |       |
	| JMD A    | Non Zero      |  33 |   063 |
	|          | Zero          |  34 |   064 |
	|          | Negative      |  35 |   065 |
	|          | Positive      |  36 |   066 |
	|          | Positive,NZ   |  37 |   067 |
	|          |               |     |       |
	| JMD B    | Non Zero      |  73 |   163 |
	|          | Zero          |  74 |   164 |
	|          | Negative      |  75 |   165 |
	|          | Positive      |  76 |   166 |
	|          | Positive,NZ   |  77 |   167 |
	|          |               |     |       |
	| JMD X    | Non Zero      |  B3 |   263 |
	|          | Zero          |  B4 |   264 |
	|          | Negative      |  B5 |   265 |
	|          | Positive      |  B6 |   266 |
	|          | Positive,NZ   |  B7 |   267 |
	|          |               |     |       |
	| JMI      | Unconditional |  FB |   373 |
	|          |               |     |       |
	| JMI A    | Non Zero      |  3B |   073 |
	|          | Zero          |  3C |   074 |
	|          | Negative      |  3D |   075 |
	|          | Positive      |  3E |   076 |
	|          | Positive,NZ   |  3F |   077 |
	|          |               |     |       |
	| JMI B    | Non Zero      |  7B |   173 |
	|          | Zero          |  7C |   174 |
	|          | Negative      |  7D |   175 |
	|          | Positive      |  7E |   176 |
	|          | Positive,NZ   |  7F |   177 |
	|          |               |     |       |
	| JMI X    | Non Zero      |  BB |   273 |
	|          | Zero          |  BC |   274 |
	|          | Negative      |  BD |   275 |
	|          | Positive      |  BE |   276 |
	|          | Positive,NZ   |  BF |   277 |
	|          |               |     |       |
	| JPD      | Unconditional |  E3 |   343 |
	|          |               |     |       |
	| JPD A    | Non Zero      |  23 |   043 |
	|          | Zero          |  24 |   044 |
	|          | Negative      |  25 |   045 |
	|          | Positive      |  26 |   046 |
	|          | Positive,NZ   |  27 |   047 |
	|          |               |     |       |
	| JPD B    | Non Zero      |  63 |   143 |
	|          | Zero          |  64 |   144 |
	|          | Negative      |  65 |   145 |
	|          | Positive      |  66 |   146 |
	|          | Positive,NZ   |  67 |   147 |
	|          |               |     |       |
	| JPD X    | Non Zero      |  A3 |   243 |
	|          | Zero          |  A4 |   244 |
	|          | Negative      |  A5 |   245 |
	|          | Positive      |  A6 |   246 |
	|          | Positive,NZ   |  A7 |   247 |
	|          |               |     |       |
	| JPI      | Unconditional |  EB |   353 |
	|          |               |     |       |
	| JPI A    | Non Zero      |  2B |   053 |
	|          | Zero          |  2C |   054 |
	|          | Negative      |  2D |   055 |
	|          | Positive      |  2E |   056 |
	|          | Positive,NZ   |  2F |   057 |
	|          |               |     |       |
	| JPI B    | Non Zero      |  6B |   153 |
	|          | Zero          |  6C |   154 |
	|          | Negative      |  6D |   155 |
	|          | Positive      |  6E |   156 |
	|          | Positive,NZ   |  6F |   157 |
	|          |               |     |       |
	| JPI X    | Non Zero      |  AB |   253 |
	|          | Zero          |  AC |   254 |
	|          | Negative      |  AD |   255 |
	|          | Positive      |  AE |   256 |
	|          | Positive,NZ   |  AF |   257 |
	|          |               |     |       |
	| LNEG     | Immediate     |  DB |   333 |
	|          | Memory        |  DC |   334 |
	|          | Indirect      |  DD |   335 |
	|          | Indexed       |  DE |   336 |
	|          | Ind/Indexed   |  DF |   337 |
	|          |               |     |       |
	| LOAD A   | Immediate     |  13 |   023 |
	|          | Memory        |  14 |   024 |
	|          | Indirect      |  15 |   025 |
	|          | Indexed       |  16 |   026 |
	|          | Ind/Indexed   |  17 |   027 |
	|          |               |     |       |
	| LOAD B   | Immediate     |  53 |   123 |
	|          | Memory        |  54 |   124 |
	|          | Indirect      |  55 |   125 |
	|          | Indexed       |  56 |   126 |
	|          | Ind/Indexed   |  57 |   127 |
	|          |               |     |       |
	| LOAD X   | Immediate     |  93 |   223 |
	|          | Memory        |  94 |   224 |
	|          | Indirect      |  95 |   225 |
	|          | Indexed       |  96 |   226 |
	|          | Ind/Indexed   |  97 |   227 |
	|          |               |     |       |
	| NOOP     |               |  80 |   200 |
	|          |               |     |       |
	| OR       | Immediate     |  C3 |   303 |
	|          | Memory        |  C4 |   304 |
	|          | Indirect      |  C5 |   305 |
	|          | Indexed       |  C6 |   306 |
	|          | Ind/Indexed   |  C7 |   307 |
	|          |               |     |       |
	| ROTL A   | 1 place       |  C9 |   311 |
	|          | 2 places      |  D1 |   321 |
	|          | 3 places      |  D9 |   331 |
	|          | 4 places      |  C1 |   301 |
	|          |               |     |       |
	| ROTL B   | 1 place       |  E9 |   351 |
	|          | 2 places      |  F1 |   361 |
	|          | 3 places      |  F9 |   371 |
	|          | 4 places      |  E1 |   341 |
	|          |               |     |       |
	| ROTR A   | 1 place       |  49 |   111 |
	|          | 2 places      |  51 |   121 |
	|          | 3 places      |  59 |   131 |
	|          | 4 places      |  41 |   101 |
	|          |               |     |       |
	| ROTR B   | 1 place       |  69 |   151 |
	|          | 2 places      |  71 |   161 |
	|          | 3 places      |  79 |   171 |
	|          | 4 places      |  61 |   141 |
	|          |               |     |       |
	| SET0     | bit 0         |  02 |   002 |
	|          | bit 1         |  0A |   012 |
	|          | bit 2         |  12 |   022 |
	|          | bit 3         |  1A |   032 |
	|          | bit 4         |  22 |   042 |
	|          | bit 5         |  2A |   052 |
	|          | bit 6         |  32 |   062 |
	|          | bit 7         |  3A |   072 |
	|          |               |     |       |
	| SET1     | bit 0         |  42 |   102 |
	|          | bit 1         |  4A |   112 |
	|          | bit 2         |  52 |   122 |
	|          | bit 3         |  5A |   132 |
	|          | bit 4         |  62 |   142 |
	|          | bit 5         |  6A |   152 |
	|          | bit 6         |  72 |   162 |
	|          | bit 7         |  7A |   172 |
	|          |               |     |       |
	| SFTL A   | 1 place       |  89 |   211 |
	|          | 2 places      |  91 |   221 |
	|          | 3 places      |  99 |   231 |
	|          | 4 places      |  81 |   201 |
	|          |               |     |       |
	| SFTL B   | 1 place       |  A9 |   251 |
	|          | 2 places      |  B1 |   261 |
	|          | 3 places      |  B9 |   271 |
	|          | 4 places      |  A1 |   241 |
	|          |               |     |       |
	| SFTR A   | 1 place       |  09 |   011 |
	|          | 2 places      |  11 |   021 |
	|          | 3 places      |  19 |   031 |
	|          | 4 places      |  01 |   001 |
	|          |               |     |       |
	| SFTR B   | 1 place       |  29 |   051 |
	|          | 2 places      |  31 |   061 |
	|          | 3 places      |  39 |   071 |
	|          | 4 places      |  21 |   041 |
	|          |               |     |       |
	| SKP0     | bit 0         |  82 |   202 |
	|          | bit 1         |  8A |   212 |
	|          | bit 2         |  92 |   222 |
	|          | bit 3         |  9A |   232 |
	|          | bit 4         |  A2 |   242 |
	|          | bit 5         |  AA |   252 |
	|          | bit 6         |  B2 |   262 |
	|          | bit 7         |  BA |   272 |
	|          |               |     |       |
	| SKP1     | bit 0         |  C2 |   302 |
	|          | bit 1         |  CA |   312 |
	|          | bit 2         |  D2 |   322 |
	|          | bit 3         |  DA |   332 |
	|          | bit 4         |  E2 |   342 |
	|          | bit 5         |  EA |   352 |
	|          | bit 6         |  F2 |   362 |
	|          | bit 7         |  FA |   372 |
	|          |               |     |       |
	| STORE A  | Immediate     |  1B |   033 |
	|          | Memory        |  1C |   034 |
	|          | Indirect      |  1D |   035 |
	|          | Indexed       |  1E |   036 |
	|          | Ind/Indexed   |  1F |   037 |
	|          |               |     |       |
	| STORE B  | Immediate     |  5B |   133 |
	|          | Memory        |  5C |   134 |
	|          | Indirect      |  5D |   135 |
	|          | Indexed       |  5E |   136 |
	|          | Ind/Indexed   |  5F |   137 |
	|          |               |     |       |
	| STORE X  | Immediate     |  9B |   233 |
	|          | Memory        |  9C |   234 |
	|          | Indirect      |  9D |   235 |
	|          | Indexed       |  9E |   236 |
	|          | Ind/Indexed   |  9F |   237 |
	|          |               |     |       |
	| SUB A    | Immediate     |  0B |   013 |
	|          | Memory        |  0C |   014 |
	|          | Indirect      |  0D |   015 |
	|          | Indexed       |  0E |   016 |
	|          | Ind/Indexed   |  0F |   017 |
	|          |               |     |       |
	| SUB B    | Immediate     |  4B |   113 |
	|          | Memory        |  4C |   114 |
	|          | Indirect      |  4D |   115 |
	|          | Indexed       |  4E |   116 |
	|          | Ind/Indexed   |  4F |   117 |
	|          |               |     |       |
	| SUB X    | Immediate     |  8B |   213 |
	|          | Memory        |  8C |   214 |
	|          | Indirect      |  8D |   215 |
	|          | Indexed       |  8E |   216 |
	|          | Ind/Indexed   |  8F |   217 |
[te]
[i-2]

[h1]	Addressing Modes:
[i2]
[tb]
	| Mode             | Syntax      |
        | ---------------- | ----------- |
	| Immediate        | C=value     |
	| Memory           | address     |
	| Indirect         | (address)   |
	| Indexed          | address,X   |
	| Indirect/Indexed | (address),X |
[te]
[i-2]
[=]
[h1]	Constants
[i2]
[tb]
	| Decimal | value  |
	| Octal   | !value |
	| Hex     | $value |
	| Binary  | %value |
[te]
[i-2]
[=]
[h1]	Special Memory Locations
[i2]
[tb]
	| Hex | Octal | Use              |
	|  00 | 000   | A Register       |
	|  01 | 001   | B Register       |
	|  02 | 002   | X Register       |
	|  03 | 003   | P Register       |
	|  80 | 200   | Output Register  |
	|  81 | 201   | A Flags Register |
	|  82 | 202   | B Flags Register |
	|  83 | 203   | X Flags Register |
	|  FF | 377   | Input Register   |
[te]
[i-2]
[=]
[h2]	Sample Programs
[=]
[h1]	Sample 1
[i2]
[tb]
	| Address | Machine Code | Assembly Code |                       |
	| 004     | 023 000      | LOAD A C=000  | ; Clear A             |
	| 006     | 034 200      | STORE A 200   | ; Write to output     |
	| 010     | 003 001      | ADD A C=001   | ; Increment by 1      |
	| 012     | 343 006      | JPD 006       | ; loop back           |
[te]
[i-2]
[=]
[h1]	Sample 2
[i2]
[tb]
	| Address | Machine Code | Assembly Code |                       |
	| 004     | 024 377      | LOAD A 377    | ; REad input register |
	| 006     | 000          | HALT          | ; Halt machine        |
	| 007     | 004 377      | ADD A 377     | ; Add in new number   |
	| 011     | 034 200      | STORE A 377   | ; Output total        |
	| 013     | 343 006      | JPD 006       | ; Loop back for more  |
[te]
[i-2]
