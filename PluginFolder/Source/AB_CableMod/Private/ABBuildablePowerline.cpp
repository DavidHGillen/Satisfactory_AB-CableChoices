// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "ABBuildablePowerline.h"

// Satic init ////


// Ctor ////
AABBuildablePowerline::AABBuildablePowerline() {}

// AActor interface ////
void AABBuildablePowerline::BeginPlay() {
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
/* Used to preview changes before application, also called redundantly on application. Colour calls but not skin 
void AABBuildablePowerline::ApplyCustomizationData_Native(const FFactoryCustomizationData& customizationData) {
	UE_LOG(LogTemp, Warning, TEXT("()()()()() ApplyCustomizationData_Native ()()()()()"));
	Super::ApplyCustomizationData_Native(customizationData);
}//*/

/* actually change customization data both skin and color  */
void AABBuildablePowerline::SetCustomizationData_Native(const FFactoryCustomizationData& customizationData) {
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