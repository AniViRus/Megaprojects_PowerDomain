#pragma once

#include "CoreMinimal.h"
#include "AVRPMegaprojectInterface.h"
#include "FGFactoryConnectionComponent.h"
#include "Buildables/FGBuildablePowerStorage.h"
#include "AVRPBuildablePowerDomain.generated.h"


USTRUCT(BlueprintType)
struct FAVRPPowerDomainPowerInfo
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float powerStoreCapacity;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float powerInputCapacity;
};
UCLASS(Abstract)
/**
 * Megaproject version of Power Storage - changes behaviour based on unlocked schematics
 **/
class MEGAPROJECTS_POWERDOMAIN_API AAVRPBuildablePowerDomain : public AFGBuildablePowerStorage, public IAVRPMegaprojectInterface
{
	GENERATED_BODY()
public:
	AAVRPBuildablePowerDomain();
	virtual void BeginPlay() override;
	virtual void Factory_Tick(float dt) override;
	// Begin AVRPMegaprojectInterface
	virtual void BeginFromLevel_Implementation(int level) override;
	virtual void OnLevelChanged_Implementation(int level) override;
	//End AVRPMegaprojectInterface

	//Begin FGActorRepresentationInterface
	virtual bool AddAsRepresentation() override;
	virtual bool UpdateRepresentation() override;
	virtual bool RemoveAsRepresentation() override;
	virtual bool IsActorStatic() override;
	virtual FVector GetRealActorLocation() override;
	virtual FRotator GetRealActorRotation() override;
	virtual class UTexture2D* GetActorRepresentationTexture() override;
	virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;
	virtual FText GetActorRepresentationText() override;
	virtual void SetActorRepresentationText(const FText& newText) override;
	virtual FLinearColor GetActorRepresentationColor() override;
	virtual void SetActorRepresentationColor(FLinearColor newColor) override;
	virtual ERepresentationType GetActorRepresentationType() override;
	virtual bool GetActorShouldShowInCompass() override;
	virtual bool GetActorShouldShowOnMap() override;
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	virtual float GetActorFogOfWarRevealRadius() override;
	virtual ECompassViewDistance GetActorCompassViewDistance() override;
	virtual void SetActorCompassViewDistance(ECompassViewDistance compassViewDistance) override;
	virtual TArray< FLocalUserNetIdBundle > GetLastEditedBy() const override;
	virtual void SetActorLastEditedBy(const TArray< FLocalUserNetIdBundle >& LastEditedBy) override;
	//End FGActorRepresentationInterface
protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FAVRPPowerDomainPowerInfo> storageConfiguration;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UMaterialInterface* mRepresentationCompassMaterial;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UTexture2D* mRepresentationTexture;
	UPROPERTY()
	TArray<UFGFactoryConnectionComponent*> connections;
private:
	UPROPERTY(Transient)
	UFGActorRepresentation* cachedRepresentation;
};