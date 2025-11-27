#include "AVRPBuildablePowerDomain.h"
#include "FGPowerInfoComponent.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "AVRPBPFL_MegaprojectsLib.h"
#include "FGSchematicManager.h"


AAVRPBuildablePowerDomain::AAVRPBuildablePowerDomain()
{
	this->connections = TArray<UFGFactoryConnectionComponent*>();
}

void AAVRPBuildablePowerDomain::BeginPlay()
{
	Super::BeginPlay();
	connections.Empty();
	ForEachComponent<UFGFactoryConnectionComponent>(true, [&](UFGFactoryConnectionComponent* FactoryConn) {
		switch (FactoryConn->GetDirection()) {
		case EFactoryConnectionDirection::FCD_INPUT:
			connections.AddUnique(FactoryConn);
			break;
		}
		});
}

void AAVRPBuildablePowerDomain::Factory_Tick(float dt)
{
	if (!HasAuthority()) return;
	Super::Factory_Tick(dt);
	UAVRPBPFL_MegaprojectsLib::Factory_PayoffOnMegagproject(this, connections);
}

void AAVRPBuildablePowerDomain::BeginFromLevel_Implementation(int level)
{
	//Enable all current phase meshes (will be done in blueprint)
	auto curConfig = storageConfiguration[level];
	mPowerStoreCapacity = curConfig.powerStoreCapacity;
	mPowerInputCapacity = curConfig.powerInputCapacity;
	if (!HasAuthority()) return;
	mPowerInfo->GetBatteryInfo()->mPowerStoreCapacity = mPowerStoreCapacity;
	mPowerInfo->GetBatteryInfo()->mPowerInputCapacity = mPowerInputCapacity;
	AddAsRepresentation(); //Call to add actor representation, remote
}

void AAVRPBuildablePowerDomain::OnLevelChanged_Implementation(int level)
{
	//Initiate sequence of enabling new phase meshes (will be done in blueprint)
	auto curConfig = storageConfiguration[level];
	mPowerStoreCapacity = curConfig.powerStoreCapacity;
	mPowerInputCapacity = curConfig.powerInputCapacity;
	if (!HasAuthority()) return;
	mPowerInfo->GetBatteryInfo()->mPowerStoreCapacity = mPowerStoreCapacity;
	mPowerInfo->GetBatteryInfo()->mPowerInputCapacity = mPowerInputCapacity;
}

bool AAVRPBuildablePowerDomain::AddAsRepresentation()
{
	if (!HasAuthority()) return false;
	if (auto manager = AFGActorRepresentationManager::Get(this)) {
		cachedRepresentation = manager->CreateAndAddNewRepresentation(this);
		return true;
	}
	return false;
}

bool AAVRPBuildablePowerDomain::UpdateRepresentation()
{
	if (!HasAuthority()) return false;
	if (auto manager = AFGActorRepresentationManager::Get(this)) {
		manager->UpdateRepresentation(cachedRepresentation);
		return true;
	}
	return false;
}

bool AAVRPBuildablePowerDomain::RemoveAsRepresentation()
{
	if (!HasAuthority()) return false;
	if (auto manager = AFGActorRepresentationManager::Get(this)) {
		manager->RemoveRepresentationOfActor(this);
		cachedRepresentation = nullptr;
		return true;
	}
	return false;
}

bool AAVRPBuildablePowerDomain::IsActorStatic()
{
	return true;
}

FVector AAVRPBuildablePowerDomain::GetRealActorLocation()
{
	return GetActorLocation();
}

FRotator AAVRPBuildablePowerDomain::GetRealActorRotation()
{
	return FRotator::ZeroRotator;
}

UTexture2D* AAVRPBuildablePowerDomain::GetActorRepresentationTexture()
{
	return mRepresentationTexture;
}

UMaterialInterface* AAVRPBuildablePowerDomain::GetActorRepresentationCompassMaterial()
{
	return mRepresentationCompassMaterial;
}

FText AAVRPBuildablePowerDomain::GetActorRepresentationText()
{
	return mDisplayName;
}

void AAVRPBuildablePowerDomain::SetActorRepresentationText(const FText& newText){}

FLinearColor AAVRPBuildablePowerDomain::GetActorRepresentationColor()
{
	return FLinearColor(.1f, .1f, .1f);
}

void AAVRPBuildablePowerDomain::SetActorRepresentationColor(FLinearColor newColor){}

ERepresentationType AAVRPBuildablePowerDomain::GetActorRepresentationType()
{
	return ERepresentationType::RT_SpaceElevator;
}

bool AAVRPBuildablePowerDomain::GetActorShouldShowInCompass()
{
	return true;
}

bool AAVRPBuildablePowerDomain::GetActorShouldShowOnMap()
{
	return true;
}

EFogOfWarRevealType AAVRPBuildablePowerDomain::GetActorFogOfWarRevealType()
{
	return EFogOfWarRevealType::FOWRT_None;
}

float AAVRPBuildablePowerDomain::GetActorFogOfWarRevealRadius()
{
	return 0.0f;
}

ECompassViewDistance AAVRPBuildablePowerDomain::GetActorCompassViewDistance()
{
	return ECompassViewDistance::CVD_Far;
}

void AAVRPBuildablePowerDomain::SetActorCompassViewDistance(ECompassViewDistance compassViewDistance){}

TArray<FLocalUserNetIdBundle> AAVRPBuildablePowerDomain::GetLastEditedBy() const
{
	return TArray<FLocalUserNetIdBundle>();
}

void AAVRPBuildablePowerDomain::SetActorLastEditedBy(const TArray<FLocalUserNetIdBundle>& LastEditedBy){}
