// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "ABBuildablePowerline.h"

// Satic init ////


// Ctor ////
AABBuildablePowerline::AABBuildablePowerline() {}

// AActor interface ////
void AABBuildablePowerline::BeginPlay() {
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() BeginPlay"));
	Super::BeginPlay();

	// fix colouration init and add my skin system adaptation

	// pull data
	TArray<UStaticMeshComponent*> powerlineMeshes = GetWireInstanceMeshes();
	TSubclassOf<UFGFactoryCustomizationDescriptor_Skin> skinDesc = mCustomizationData.SkinDesc;
	bool bValidSkin = skinDesc != NULL && skinDesc.GetDefaultObject()->ID != -1;

	// reference mine
	FABPowerlineCustomization* currentSkinData = skinToData.Find(bValidSkin ? skinDesc : NULL);
	UMaterialInterface* powerlineMat = currentSkinData != NULL ? currentSkinData->material : NULL;
	UNiagaraSystem* powerlineFX = currentSkinData != NULL ? currentSkinData->particleFX : NULL;

	// apply
	for (int32 i = 0, l = powerlineMeshes.Num(); i < l; i++) {
		UFGBlueprintFunctionLibrary::ApplyCustomizationPrimitiveData(this, mCustomizationData, 0, powerlineMeshes[i]);
		if (powerlineMat != NULL) { powerlineMeshes[i]->SetMaterial(0, powerlineMat); }
		//if (powerlineFX != nullptr) {
	}
}

// Factory interface ////
/** Used to preview changes before application, also called redundantly on application.Colour calls but not skin */
void AABBuildablePowerline::ApplyCustomizationData_Native(const FFactoryCustomizationData& customizationData) {
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() ApplyCustomizationData_Native"));
	Super::ApplyCustomizationData_Native(customizationData);
}

/** actually change customization data both skin and color  */
void AABBuildablePowerline::SetCustomizationData_Native(const FFactoryCustomizationData& customizationData) {
	UE_LOG(LogTemp, Warning, TEXT("()( )()( )() SetCustomizationData_Native"));
	Super::SetCustomizationData_Native(customizationData);

	// add my skin system adaptation

	// pull data
	TArray<UStaticMeshComponent*> powerlineMeshes = GetWireInstanceMeshes();
	TSubclassOf<UFGFactoryCustomizationDescriptor_Skin> skinDesc = customizationData.SkinDesc;
	bool bValidSkin = skinDesc != NULL && skinDesc.GetDefaultObject()->ID != -1;

	// reference mine
	FABPowerlineCustomization* currentSkinData = skinToData.Find(bValidSkin ? skinDesc : NULL);
	UMaterialInterface* powerlineMat = currentSkinData != NULL ? currentSkinData->material : NULL;
	UNiagaraSystem* powerlineFX = currentSkinData != NULL ? currentSkinData->particleFX : NULL;

	// apply
	for (int32 i = 0, l = powerlineMeshes.Num(); i < l; i++) {
		if (powerlineMat != nullptr) { powerlineMeshes[i]->SetMaterial(0, powerlineMat); }
		//if (powerlineFX != nullptr) {
	}
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
}