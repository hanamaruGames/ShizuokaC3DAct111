//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１                             ver 3.2        2023.1.31
//		武器・全体の処理
//															Weapon.cpp
//=============================================================================
#include  "Weapon.h"

//=============================================================================================================================
//
// 武器メインプロシージャのコンストラクタ
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
// ----------------------------------------------------------------------------------------------------------------------------
CWeaponProc::CWeaponProc()
{
	Instantiate<CWeaponLaserProc>();
//	m_pWeaponLaserProc = new CWeaponLaserProc();		// 武器・レーザープロシージャ
//	m_pProcArray.push_back(m_pWeaponLaserProc);				// プロシージャをプロシージャ配列に登録する

	Instantiate<CWeaponHoldProc>();
//	m_pWeaponHoldProc = new CWeaponHoldProc();		// 武器・手に持つアイテムのプロシージャ
//	m_pProcArray.push_back(m_pWeaponHoldProc);				// プロシージャをプロシージャ配列に登録する
}
