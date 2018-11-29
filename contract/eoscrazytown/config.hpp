#pragma once
#ifndef _DFF_CONFIG_HPP

#define EOS_SYMBOL S(4, EOS)
#define CTN_SYMBOL S(4, CTN)

#define TOKEN_SYMBOL CTN_SYMBOL
#define TOKEN_CONTRACT N(dacincubator)

#define PROXY N(winninetysix)
#define PROXY_STRING "winninetysix"

const uint128_t MAGNITUDE = 1ll<<32;

#define SIDE 0.98
#define DRAW 8
#define COLOR 0.96
#define ODD 0.82
#define EVEN 1.12

#endif

/*
new(20181129):
(1)	龙赢：0.98
(2)	虎赢：0.98
(3)	和：8
(4)	龙红：0.96
(5)	虎红：0.96
(6)	龙黑：0.96
(7)	虎黑：0.96
(8)	龙单：0.82
(9)	龙双：1.12
(10) 虎单：0.82
(11) 虎双：1.12



old:
#define SIDE 0.98
#define DRAW 8
#define COLOR 0.9
#define ODD 0.75
#define EVEN 1.05

#endif

(1)	龙赢：龙方牌面数值大于虎方
(2)	虎赢：虎方牌面数值大于龙方
(3)	和：双方牌面数值一样大
(4)	龙红：龙方牌面的花色为红色（即红桃牌或者方块牌）
(5)	虎红：虎方牌面的花色为红色（即红桃牌或者方块牌）
(6)	龙黑：龙方牌面的花色为黑色（即黑桃牌或者梅花牌）
(7)	虎黑：虎方牌面的花色为黑色（即黑桃牌或者梅花牌）
(8)	龙单：龙方牌面数值为奇数（1.3.5这种）
(9)	龙双：龙方牌面数值为偶数（2.4.6这种）
(10) 虎单：虎方牌面数值为奇数（1.3.5这种）
(11) 虎双：虎方牌面数值为偶数（2.4.6这种）

1. 0.98
2. 0.98
3. 8
4. 0.9
5. 0.9
6. 0.9
7. 0.9
8. 0.75
9. 1.05
10. 0.75
11. 1.05
*/
