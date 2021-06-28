#include "units.h"

BOOL ProvMenuOpen = FALSE;
//INT NumOfProvinces;
tk3PROVINCE TK3_Provinces[PROVINCES_AMOUNT];

tk3PROVINCE TK3_GenerateProvince( CHAR *ProvName, INT Dev, INT Castle, CHAR *Owner )
{
  tk3PROVINCE x;
  x.ProvName = ProvName;
  x.ProvDev = Dev;
  x.CastleLevel = Castle;
  x.Owner = Owner;
  //NumOfProvinces++;
  return x;
}

VOID TK3_GenerateProvinceList( VOID )
{
  TK3_Provinces[0] = TK3_GenerateProvince("Brittany", 18, 0, "Brittany");
  TK3_Provinces[1] = TK3_GenerateProvince("Wales", 6, 1, "England");
  TK3_Provinces[2] = TK3_GenerateProvince("London", 16, 0, "England");
  TK3_Provinces[3] = TK3_GenerateProvince("Cornwall", 11, 0, "England");
}

