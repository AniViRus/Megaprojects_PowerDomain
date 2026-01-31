#pragma once

#include "CoreMinimal.h"
#include "FGConstructDisqualifier.h"
#include "AVRPBuildablePowerDomain.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "Hologram/FGPowerPoleHologram.h"
#include "AVRPPowerDomainHologram.generated.h"

#define LOCTEXT_NAMESPACE "Megaprojects_PowerDomainLocnamespace"
UCLASS()
class MEGAPROJECTS_POWERDOMAIN_API UPowerSatelliteCD_NoPowerDomain : public UFGConstructDisqualifier
{
	GENERATED_BODY()
public:
	UPowerSatelliteCD_NoPowerDomain()
	{
		mDisqfualifyingText = LOCTEXT("PowerSatelliteCD_NoPowerDomain", "Power Domain not found!");
	}
};
#undef LOCTEXT_NAMESPACE
/**
 * Power Satellite hologram which aims to disqualify building if Power Domain isn't initiated
 */
UCLASS()
class MEGAPROJECTS_POWERDOMAIN_API AAVRPPowerDomainHologram : public AFGPowerPoleHologram
{
	GENERATED_BODY()
	//Begin AFGHologram interface
	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual bool TryUpgrade(const FHitResult& hitResult) override;
	virtual AActor* GetUpgradedActor() const override;
	virtual void OnInvalidHitResult() override;
	//End AFGHologram interface
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AAVRPMegaprojectSubsystemBase> megaprojectClass;
};
