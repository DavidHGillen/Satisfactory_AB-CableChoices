// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "ABBuildablePowerline.h"

// Satic init ////


// Ctor ////
AABBuildablePowerline::AABBuildablePowerline() {}

// AActor interface ////
void AABBuildablePowerline::BeginPlay() {
	Super::BeginPlay();

	// fix colouration init
	TArray<UStaticMeshComponent*> powerlineMeshes = GetWireInstanceMeshes();
	FABPowerlineCustomization* currentSkinData = skinToData.Find(mCustomizationData.SkinDesc);

	UMaterialInterface* powerlineMat = currentSkinData != NULL ? currentSkinData->material : NULL;
	UNiagaraSystem* powerlineFX = currentSkinData != NULL ? currentSkinData->particleFX : NULL;

	for (int32 i = 0, l = powerlineMeshes.Num(); i < l; i++) {
		UFGBlueprintFunctionLibrary::ApplyCustomizationPrimitiveData(this, mCustomizationData, 0, powerlineMeshes[i]);
		if (powerlineMat != NULL) { powerlineMeshes[i]->SetMaterial(0, powerlineMat); }
		//if (powerlineFX != nullptr) {
	}
}

// Factory interface ////
/* Used to preview changes before application, also called redundantly on application. Colour calls but not skin 
void AABBuildablePowerline::ApplyCustomizationData_Native(const FFactoryCustomizationData& customizationData) {
	UE_LOG(LogTemp, Warning, TEXT("()()()()() ApplyCustomizationData_Native ()()()()()"));
	Super::ApplyCustomizationData_Native(customizationData);
}//*/

/* actually change customization data both skin and color  */
void AABBuildablePowerline::SetCustomizationData_Native(const FFactoryCustomizationData& customizationData) {
	Super::SetCustomizationData_Native(customizationData);

	TArray<UStaticMeshComponent*> powerlineMeshes = GetWireInstanceMeshes();
	FABPowerlineCustomization* currentSkinData = skinToData.Find(customizationData.SkinDesc);

	UMaterialInterface* powerlineMat = currentSkinData != nullptr ? currentSkinData->material : nullptr;
	UNiagaraSystem* powerlineFX = currentSkinData != nullptr ? currentSkinData->particleFX : nullptr;

	for (int32 i = 0, l = powerlineMeshes.Num(); i < l; i++) {
		if (powerlineMat != nullptr) { powerlineMeshes[i]->SetMaterial(0, powerlineMat); }
		//if (powerlineFX != nullptr) {
	}
}