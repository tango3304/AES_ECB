#ifndef Function_IncludeGuard
#define Function_IncludeGuard
//=================================
//グローバル関数プロトタイプ宣言
//=================================
//・SubBytes
//S-BOX表の値に変換する関数
extern int Encryption_SBOX_CHANGE(int);
extern int Decryption_SBOX_CHANGE(int);

//・MixColumns
//【暗号化】
//0x02と0x01の計算処理関数
extern int MixColumns_MDS_xor_0x02or01(int, int);
//0x03の計算処理関数
extern int MixColumns_MDS_xor_0x03(int, int);

//【復号化】
/*x3乗の計算処理関数*/
extern int InvMixColumns_x3(int);
/*x2乗の計算処理関数*/
extern int InvMixColumns_x2(int);
/*xの計算処理関数*/
extern int InvMixColumns_x(int);
/*1の計算処理関数*/
extern int InvMixColumns_1(int);

/*Eの計算処理関数*/
extern int InvMixColumns_E(int);
/*Bの計算処理関数*/
extern int InvMixColumns_B(int);
/*Dの計算処理関数*/
extern int InvMixColumns_D(int);
/*9の計算処理関数*/
extern int InvMixColumns_9(int);



#endif //Function_IncludeGuard
