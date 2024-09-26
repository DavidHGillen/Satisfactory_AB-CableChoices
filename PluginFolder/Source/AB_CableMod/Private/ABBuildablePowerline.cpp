// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "ABBuildablePowerline.h"

// Satic init ////


// Ctor ////
AABBuildablePowerline::AABBuildablePowerline() {}

// AActor interface ////
void AABBuildablePowerline::BeginPlay() {
	Super::BeginPlay();

	// fix colouration init and add my skin system adaptation
	// delay necessary because some construction processes cause other things like build effects to run interference
	FTimerDelegate Bypass;
	Bypass.BindLambda([&]() {
		ApplyCustomizationData_Native(mCustomizationData);
	});
	GetWorldTimerManager().SetTimerForNextTick(Bypass);
}

// Factory interface ////
void AABBuildablePowerline::ApplyCustomizationData_Native(const FFactoryCustomizationData & customizationData) {
	//UE_LOG(LogTemp, Warning, TEXT("()( )()( )() ApplyCustomizationData_Native"));
	Super::ApplyCustomizationData_Native(customizationData);

	// add my skin system adaptation //

	// pull data
	TArray<UStaticMeshComponent*> powerlineMeshes = GetWireInstanceMeshes();
	TSubclassOf<UFGFactoryCustomizationDescriptor_Skin> skinDesc = customizationData.SkinDesc;
	int lineCount = powerlineMeshes.Num();

	// reference mine
	FABPowerlineCustomization* currentSkinData = skinToData.Find(skinDesc);
	if (currentSkinData == nullptr) { currentSkinData = &defaultData; }

	UMaterialInterface* powerlineMat = currentSkinData->material;
	UNiagaraSystem* powerlineFX = currentSkinData->particleFX;

	// apply
	for (int i = 0; i < lineCount; i++) {
		//UE_LOG(LogTemp, Warning, TEXT("()( )()( )() set %d"), i);
		powerlineMeshes[i]->SetMaterial(0, powerlineMat);
		powerlineMeshes[i]->SetCollisionProfileName("BuildingMesh", false); //can't target for customization w/o. luckily this is forced to run on beign play
		//if (powerlineFX != nullptr) {
	}
}

/*
void AABBuildablePowerline::OnBuildEffectFinished() {
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() OnBuildEffectFinished"));
	Super::OnBuildEffectFinished();
	//ApplyCustomizationData_Native(mCustomizationData);
}

void AABBuildablePowerline::PostLazySpawnInstances_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() PostLazySpawnInstances_Implementation"));
	Super::PostLazySpawnInstances_Implementation();
}

void AABBuildablePowerline::Native_OnMaterialInstancesUpdated() {
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() Native_OnMaterialInstancesUpdated"));
	Super::Native_OnMaterialInstancesUpdated();
}

void AABBuildablePowerline::SetCustomizationData_Native(const FFactoryCustomizationData& customizationData) {
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() SetCustomizationData_Native"));
	Super::SetCustomizationData_Native(customizationData);
}

TSubclassOf<UFGFactoryCustomizationDescriptor_Skin> AABBuildablePowerline::GetActiveSkin_Native()
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() GetActiveSkin_Native"));
	return Super::GetActiveSkin_Native();
}

TSubclassOf<UFGFactoryCustomizationDescriptor_Skin> AABBuildablePowerline::GetActiveSkin_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() GetActiveSkin_Implementation"));
	return Super::GetActiveSkin_Implementation();
}

bool AABBuildablePowerline::IsColorApplicationDeferred()
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() IsColorApplicationDeferred"));
	return Super::IsColorApplicationDeferred();
}

bool AABBuildablePowerline::CanApplyDeferredColorToBuildable(FVector hitLocation, FVector hitNormal, TSubclassOf<class UFGFactoryCustomizationDescriptor_Swatch> swatch, APlayerController* playerController)
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() CanApplyDeferredColorToBuildable"));
	return Super::CanApplyDeferredColorToBuildable(hitLocation, hitNormal, swatch, playerController);
}

void AABBuildablePowerline::ApplyDeferredColorToBuildable(FVector hitLocation, TSubclassOf<class UFGFactoryCustomizationDescriptor_Swatch> swatch, APlayerController* playerController)
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() ApplyDeferredColorToBuildable"));
	Super::ApplyDeferredColorToBuildable(hitLocation, swatch, playerController);
}

void AABBuildablePowerline::StartIsAimedAtForColor_Implementation(AFGCharacterPlayer* byCharacter, bool isValid)
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() StartIsAimedAtForColor_Implementation"));
	Super::StartIsAimedAtForColor_Implementation(byCharacter, isValid);
}

void AABBuildablePowerline::StopIsAimedAtForColor_Implementation(AFGCharacterPlayer* byCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() StopIsAimedAtForColor_Implementation"));
	Super::StopIsAimedAtForColor_Implementation(byCharacter);
}

bool AABBuildablePowerline::GetCanBeColored_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() GetCanBeColored_Implementation"));
	return Super::GetCanBeColored_Implementation();
}

bool AABBuildablePowerline::GetCanBePatterned_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() GetCanBePatterned_Implementation"));
	return Super::GetCanBePatterned_Implementation();
}

void AABBuildablePowerline::OnMaterialInstancesUpdated()
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() OnMaterialInstancesUpdated"));
	Super::OnMaterialInstancesUpdated();
}

void AABBuildablePowerline::OnSkinCustomizationApplied(TSubclassOf<class UFGFactoryCustomizationDescriptor_Skin> skin)
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() OnSkinCustomizationApplied"));
	Super::OnSkinCustomizationApplied(skin);
}

void AABBuildablePowerline::ApplySkinData(TSubclassOf<UFGFactoryCustomizationDescriptor_Skin> newSkinDesc)
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() ApplySkinData"));
	Super::ApplySkinData(newSkinDesc);
}

void AABBuildablePowerline::ApplyMeshPrimitiveData(const FFactoryCustomizationData& customizationData)
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() ApplyMeshPrimitiveData"));
	Super::ApplyMeshPrimitiveData(customizationData);
}

void AABBuildablePowerline::OnRep_CustomizationData()
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() OnRep_CustomizationData"));
	Super::OnRep_CustomizationData();
}

void AABBuildablePowerline::ApplyCustomizationData_Implementation(const FFactoryCustomizationData& customizationData)
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() ApplyCustomizationData_Implementation"));
	Super::ApplyCustomizationData_Implementation(customizationData);
}
void AABBuildablePowerline::SetCustomizationData_Implementation(const FFactoryCustomizationData& customizationData)
{
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() SetCustomizationData_Implementation"));
	Super::SetCustomizationData_Implementation(customizationData);
}*/