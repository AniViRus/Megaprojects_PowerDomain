#include "AVRPPowerDomainHologram.h"
#include "AVRPMegaprojectsManager.h"

bool AAVRPPowerDomainHologram::IsValidHitResult(const FHitResult& hitResult) const
{
	bool powerDomain = false;
	auto megaprojects = AAVRPMegaprojectsManager::Get(this)->GetMegaprojects();
	for (auto megaproject : megaprojects) {
		if (megaproject->IsA(megaprojectClass)) {
			if (IsValid(megaproject->mMegaprojectInstance.GetObject())) powerDomain = true;
				break;
			}
		}
	if (!powerDomain) {
		return false;
	}
	return Super::IsValidHitResult(hitResult);
}

bool AAVRPPowerDomainHologram::TryUpgrade(const FHitResult& hitResult)
{
	return false;
}

AActor* AAVRPPowerDomainHologram::GetUpgradedActor() const
{
	return nullptr;
}

void AAVRPPowerDomainHologram::OnInvalidHitResult()
{
	AddConstructDisqualifier(UPowerSatelliteCD_NoPowerDomain::StaticClass());
}
