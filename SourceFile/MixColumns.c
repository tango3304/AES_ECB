#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../HeaderFile/FunctionDeclaration.h"//関数宣言
#include "../HeaderFile/VariableDeclaration.h"//変数宣言
#define Inv_Galois_Value (0x02)

//=====================================
//0x02と0x01の計算処理関数
//=====================================
int MixColumns_MDS_xor_0x02or01(int Galois_Value, int ShiftRows_Value){
    MixColumns_Value = 0;
    MixColumn_aDigit = 0;
    MixColumn_TenDigits = 0;
    MixColumn_MoveUP = 0;

    //1桁目と2桁目の値を分断
    MixColumn_TenDigits = ShiftRows_Value / 0x10;
    MixColumn_aDigit = ShiftRows_Value % 0x10;

    //1桁目の計算
    MixColumn_aDigit *= Galois_Value;
    if(MixColumn_aDigit >= 0x10){
        MixColumn_aDigit ^= 0x10;
        MixColumn_MoveUP = 1;
    }

    //2桁目の計算
    MixColumn_TenDigits = (MixColumn_TenDigits * Galois_Value) + MixColumn_MoveUP;

    //MixColumn_TenDigitsとMixColumn_aDigitを連結させる
    MixColumns_Value = (MixColumn_TenDigits * 0x10) + MixColumn_aDigit;

    //二桁目が繰り上がりの場合の処理
    if( MixColumns_Value >= 0x100){
        MixColumns_Value ^= 0x11B;
    }

    return MixColumns_Value;
}

//=====================================
//0x03の計算処理関数（Point関数）
//=====================================
int MixColumns_MDS_xor_0x03(int Galois_Value, int ShiftRows_Value){
    Galois_Value ^= ShiftRows_Value;

    return Galois_Value;
}

//=====================================
//x3乗の計算処理関数（Point関数）
//=====================================
int InvMixColumns_x3(int InvMixColumns_Value_x3){
    InvMixColumn_aDigit = 0; //1桁目の値を0にリセット
    InvMixColumn_TenDigits = 0; //2桁目の値を0にリセット

    for(InvMix_COUNT = 3; InvMix_COUNT > 0; InvMix_COUNT--){
        //1桁目と2桁目の値を分断
        InvMixColumn_TenDigits = InvMixColumns_Value_x3 / 0x10;
        InvMixColumn_aDigit = InvMixColumns_Value_x3 % 0x10;
        
        //1桁目の計算
        InvMixColumn_aDigit *= Inv_Galois_Value;
        if(InvMixColumn_aDigit >= 0x10){
            InvMixColumn_aDigit ^= 0x10;
            InvMixColumn_MoveUP = 1;
        }

        //2桁目の計算
        InvMixColumn_TenDigits = (InvMixColumn_TenDigits * Inv_Galois_Value) + InvMixColumn_MoveUP;

        //MixColumn_TenDigitsとMixColumn_aDigitを連結させる
        InvMixColumns_Value_x3 = (InvMixColumn_TenDigits * 0x10) + InvMixColumn_aDigit;

        //二桁目が繰り上がりの場合の処理
        if(InvMixColumns_Value_x3 >= 0x100){
            InvMixColumns_Value_x3 ^= 0x11B;
        }

        InvMixColumn_MoveUP = 0; //1桁目の繰り上がりの値を0にリセット
    }
    return InvMixColumns_Value_x3;
}

//=====================================
//x2乗の計算処理関数（Point関数）
//=====================================
int InvMixColumns_x2(int InvMixColumns_Value_x2){
    InvMixColumn_aDigit = 0; //1桁目の値を0にリセット
    InvMixColumn_TenDigits = 0; //2桁目の値を0にリセット

    for(InvMix_COUNT = 2; InvMix_COUNT > 0; InvMix_COUNT--){        
        //1桁目と2桁目の値を分断
        InvMixColumn_TenDigits = InvMixColumns_Value_x2 / 0x10;
        InvMixColumn_aDigit = InvMixColumns_Value_x2 % 0x10;
        
        //1桁目の計算
        InvMixColumn_aDigit *= Inv_Galois_Value;
        if(InvMixColumn_aDigit >= 0x10){
            InvMixColumn_aDigit ^= 0x10;
            InvMixColumn_MoveUP = 1;
        }

        //2桁目の計算
        InvMixColumn_TenDigits = (InvMixColumn_TenDigits * Inv_Galois_Value) + InvMixColumn_MoveUP;

        //MixColumn_TenDigitsとMixColumn_aDigitを連結させる
        InvMixColumns_Value_x2 = (InvMixColumn_TenDigits * 0x10) + InvMixColumn_aDigit;

        //二桁目が繰り上がりの場合の処理
        if( InvMixColumns_Value_x2 >= 0x100){
            InvMixColumns_Value_x2 ^= 0x11B;
        }

        InvMixColumn_MoveUP = 0; //1桁目の繰り上がりの値を0にリセット
    }
    return InvMixColumns_Value_x2;
}

//=====================================
//xの計算処理関数（Point関数）
//=====================================
int InvMixColumns_x(int InvMixColumns_Value_x){
    InvMixColumn_aDigit = 0; //1桁目の値を0にリセット
    InvMixColumn_MoveUP = 0; //1桁目の繰り上がりの値を0にリセット
    InvMixColumn_TenDigits = 0; //2桁目の値を0にリセット

    //1桁目と2桁目の値を分断
    InvMixColumn_TenDigits = InvMixColumns_Value_x / 0x10;
    InvMixColumn_aDigit = InvMixColumns_Value_x % 0x10;
        
    //1桁目の計算
    InvMixColumn_aDigit *= Inv_Galois_Value;
    if(InvMixColumn_aDigit >= 0x10){
        InvMixColumn_aDigit ^= 0x10;
        InvMixColumn_MoveUP = 1;
    }

    //2桁目の計算
    InvMixColumn_TenDigits = (InvMixColumn_TenDigits * Inv_Galois_Value) + InvMixColumn_MoveUP;

    //MixColumn_TenDigitsとMixColumn_aDigitを連結させる
    InvMixColumns_Value_x = (InvMixColumn_TenDigits * 0x10) + InvMixColumn_aDigit;

    //二桁目が繰り上がりの場合の処理
    if( InvMixColumns_Value_x >= 0x100){
        InvMixColumns_Value_x ^= 0x11B;
    }
    InvMixColumn_MoveUP = 0; //1桁目の繰り上がりの値を0にリセット

    return InvMixColumns_Value_x;
}

//=====================================
//1の計算処理関数（Point関数）
//=====================================
int InvMixColumns_1(int InvMixColumns_Value_1){
    InvMixColumns_Value_1 *= 0x01;

    return InvMixColumns_Value_1;
}

//=====================================
//Eの計算処理関数（Point関数）
//=====================================
int InvMixColumns_E(int InvMixColumns){
    x3_Value = P_InvMixColumns_x3(InvMixColumns);
    x2_Value = P_InvMixColumns_x2(InvMixColumns);
    x_Value = P_InvMixColumns_x(InvMixColumns);

    InvMixColumns_E_Value = x3_Value ^ x2_Value ^ x_Value;
    return InvMixColumns_E_Value;
}

//=====================================
//Bの計算処理関数（Point関数）
//=====================================
int InvMixColumns_B(int InvMixColumns){
    x3_Value = P_InvMixColumns_x3(InvMixColumns);
    x_Value = P_InvMixColumns_x(InvMixColumns);
    _1Value = P_InvMixColumns_1(InvMixColumns);

    InvMixColumns_B_Value = x3_Value ^ x_Value ^ _1Value;
    return InvMixColumns_B_Value;
}

//=====================================
//Dの計算処理関数（Point関数）
//=====================================
int InvMixColumns_D(int InvMixColumns){
    x3_Value = P_InvMixColumns_x3(InvMixColumns);
    x2_Value = P_InvMixColumns_x2(InvMixColumns);
    _1Value = P_InvMixColumns_1(InvMixColumns);

    InvMixColumns_D_Value = x3_Value ^ x2_Value ^ _1Value;
    return InvMixColumns_D_Value;
}

//=====================================
//9の計算処理関数（Point関数）
//=====================================
int InvMixColumns_9(int InvMixColumns){
    x3_Value = P_InvMixColumns_x3(InvMixColumns);
    _1Value = P_InvMixColumns_1(InvMixColumns);

    InvMixColumns_9_Value = x3_Value ^ _1Value;
    return InvMixColumns_9_Value;
}
