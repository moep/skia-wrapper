#include "test.h"

EineKlasse::EineKlasse()
: m_eineVariable(0)
{
  // weitere Initialisierungen des Objekts
}

EineKlasse::EineKlasse(int a)
: m_eineVariable(a)
{
  // weitere Initialisierungen
}

EineKlasse::~EineKlasse()
{
}

int EineKlasse::eineFunktion(int a)
{
  int ergebnis = m_eineVariable * a;
  return ergebnis;
}
