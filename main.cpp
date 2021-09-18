#include <mod/amlmod.h>
#include <mod/config.h>

MYMODCFG(net.rusjj.gtasa.eula, Accept EULA, 1.0, RusJJ)
NEEDGAME(com.rockstargames.gtasa)

uintptr_t pSCAndLib = 0;
ConfigEntry* pEULAAccepted;

extern "C" void OnModLoad()
{
    pSCAndLib = aml->GetLib("libSCAnd.so");
    if(pSCAndLib)
    {
        pEULAAccepted = cfg->Bind("AcceptEULA", false);
        if(pEULAAccepted->GetBool())
        {
            aml->Unprot(pSCAndLib + 0x31C149, 1);
            *(bool*)(pSCAndLib + 0x31C149) = true;
            return;
        }
        pEULAAccepted->SetBool(true);
        cfg->Save();
    }
}