// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "ABBuildablePowerline.h"
#include "Kismet/GameplayStatics.h"

// Satic init ////


// Ctor ////
AABBuildablePowerline::AABBuildablePowerline() {}

// AActor interface ////
void AABBuildablePowerline::BeginPlay() {
	////UE_LOG(LogTemp, Warning, TEXT("(((( Begin Play"));
	Super::BeginPlay();
	////UE_LOG(LogTemp, Warning, TEXT(")--( Begin Play"));

	// delay necessary because build is delayed when also placing poles
	FTimerDelegate Bypass;
	Bypass.BindLambda([&]() {
		ApplyCustomizationData_Native(mCustomizationData);
	});
	GetWorldTimerManager().SetTimerForNextTick(Bypass);

	////UE_LOG(LogTemp, Warning, TEXT(")))) Begin Play"));
}

void AABBuildablePowerline::UpdateIfYours(const FWireInstance* changedWire) {
	////UE_LOG(LogTemp, Warning, TEXT("(--) UpdateIfYours"));
	UWorld* world = changedWire->WireMesh->GetWorld();
	TArray<AActor*> powerlines = TArray<AActor*>();

	if (world == NULL) { return; }

	// DHG: Yeah this is gross, but until I find where an upgrade in place occurs in the buildgun, this has gotta be it.
	UGameplayStatics::GetAllActorsOfClass(world, AABBuildablePowerline::StaticClass(), powerlines);

	for (int i = powerlines.Num() - 1; i >= 0; i--) { // check most recent lines first?
		AABBuildablePowerline* line = Cast<AABBuildablePowerline>(powerlines[i]);

		for (int j = line->mWireInstances.Num() - 1; j >= 0; j--) {
			if (&(line->mWireInstances[j]) == changedWire) {
				line->ApplyCustomizationData_Native(line->mCustomizationData);
				return;
			}
		}
	}
}

// Factory interface ////
void AABBuildablePowerline::ApplyCustomizationData_Native(const FFactoryCustomizationData & customizationData) {
	////UE_LOG(LogTemp, Warning, TEXT("(((( ApplyCustomizationData_Native"));
	Super::ApplyCustomizationData_Native(customizationData);
	////UE_LOG(LogTemp, Warning, TEXT(")--( ApplyCustomizationData_Native"));

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
		////UE_LOG(LogTemp, Warning, TEXT("(((( set %d"), i);
		powerlineMeshes[i]->SetMaterial(0, powerlineMat);
		//if (powerlineFX != nullptr) {
	}
	////UE_LOG(LogTemp, Warning, TEXT(")))) ApplyCustomizationData_Native"));
}

/* ^^^
Debugging
void AABBuildablePowerline::OnConstruction(const FTransform& transform) {
	////UE_LOG(LogTemp, Warning, TEXT("(((( OnConstruction"));
	Super::OnConstruction(transform);
	////UE_LOG(LogTemp, Warning, TEXT(")))) OnConstruction"));
}

bool AABBuildablePowerline::Connect(UFGCircuitConnectionComponent* first, UFGCircuitConnectionComponent* second) {
	////UE_LOG(LogTemp, Warning, TEXT("(--) Connect"));
	return Super::Connect(first, second);
}

FFactoryCustomizationData AABBuildablePowerline::GetCustomizationData_Implementation() {
	////UE_LOG(LogTemp, Warning, TEXT("(--) GetCustomizationData_Implementation"));
	return Super::GetCustomizationData_Implementation();
}

FFactoryCustomizationData& AABBuildablePowerline::GetCustomizationData_Native() {
	////UE_LOG(LogTemp, Warning, TEXT("(--) GetCustomizationData_Native"));
	return Super::GetCustomizationData_Native();
}

TSubclassOf<UFGFactorySkinActorData> AABBuildablePowerline::GetFactorySkinClass_Implementation() {
	////UE_LOG(LogTemp, Warning, TEXT("(--) GetFactorySkinClass_Implementation"));
	return Super::GetFactorySkinClass_Implementation();
}

TSubclassOf<UFGFactorySkinActorData> AABBuildablePowerline::GetFactorySkinClass_Native() {
	////UE_LOG(LogTemp, Warning, TEXT("(--) GetFactorySkinClass_Native"));
	return Super::GetFactorySkinClass_Native();
}


void AABBuildablePowerline::PlayBuildEffects(AActor* inInstigator) {
	////UE_LOG(LogTemp, Warning, TEXT("(((( PlayBuildEffects"));
	Super::PlayBuildEffects(inInstigator);
	////UE_LOG(LogTemp, Warning, TEXT(")))) PlayBuildEffects"));
}

void AABBuildablePowerline::ExecutePlayBuildEffects() {
	////UE_LOG(LogTemp, Warning, TEXT("(((( ExecutePlayBuildEffects"));
	Super::ExecutePlayBuildEffects();
	////UE_LOG(LogTemp, Warning, TEXT(")))) ExecutePlayBuildEffects"));
}

void AABBuildablePowerline::OnBuildEffectFinished() {
	////UE_LOG(LogTemp, Warning, TEXT("(((( OnBuildEffectFinished"));
	Super::OnBuildEffectFinished();
	////UE_LOG(LogTemp, Warning, TEXT(")))) OnBuildEffectFinished"));
}

void AABBuildablePowerline::Native_OnMaterialInstancesUpdated() {
	////UE_LOG(LogTemp, Warning, TEXT("(((( Native_OnMaterialInstancesUpdated"));
	Super::Native_OnMaterialInstancesUpdated();
	////UE_LOG(LogTemp, Warning, TEXT(")))) Native_OnMaterialInstancesUpdated"));
}

void AABBuildablePowerline::SetCustomizationData_Native(const FFactoryCustomizationData& customizationData, bool skipCombine) {
	////UE_LOG(LogTemp, Warning, TEXT("(((( SetCustomizationData_Native"));
	Super::SetCustomizationData_Native(customizationData, skipCombine);
	////UE_LOG(LogTemp, Warning, TEXT(")))) SetCustomizationData_Native"));
}

TSubclassOf<UFGFactoryCustomizationDescriptor_Skin> AABBuildablePowerline::GetActiveSkin_Native() {
	////UE_LOG(LogTemp, Warning, TEXT("(--) GetActiveSkin_Native"));
	return Super::GetActiveSkin_Native();
}

TSubclassOf<UFGFactoryCustomizationDescriptor_Skin> AABBuildablePowerline::GetActiveSkin_Implementation() {
	////UE_LOG(LogTemp, Warning, TEXT("(--) GetActiveSkin_Implementation"));
	return Super::GetActiveSkin_Implementation();
}

bool AABBuildablePowerline::IsColorApplicationDeferred() {
	////UE_LOG(LogTemp, Warning, TEXT("(--) IsColorApplicationDeferred"));
	return Super::IsColorApplicationDeferred();
}

bool AABBuildablePowerline::CanApplyDeferredColorToBuildable(FVector hitLocation, FVector hitNormal, TSubclassOf<class UFGFactoryCustomizationDescriptor_Swatch> swatch, APlayerController* playerController) {
	////UE_LOG(LogTemp, Warning, TEXT("(--) CanApplyDeferredColorToBuildable"));
	return Super::CanApplyDeferredColorToBuildable(hitLocation, hitNormal, swatch, playerController);
}

void AABBuildablePowerline::ApplyDeferredColorToBuildable(FVector hitLocation, TSubclassOf<class UFGFactoryCustomizationDescriptor_Swatch> swatch, APlayerController* playerController) {
	////UE_LOG(LogTemp, Warning, TEXT("(((( ApplyDeferredColorToBuildable"));
	Super::ApplyDeferredColorToBuildable(hitLocation, swatch, playerController);
	////UE_LOG(LogTemp, Warning, TEXT(")))) ApplyDeferredColorToBuildable"));
}

void AABBuildablePowerline::StartIsAimedAtForColor_Implementation(AFGCharacterPlayer* byCharacter, bool isValid) {
	////UE_LOG(LogTemp, Warning, TEXT("(((( StartIsAimedAtForColor_Implementation"));
	Super::StartIsAimedAtForColor_Implementation(byCharacter, isValid);
	////UE_LOG(LogTemp, Warning, TEXT(")))) StartIsAimedAtForColor_Implementation"));
}

void AABBuildablePowerline::StopIsAimedAtForColor_Implementation(AFGCharacterPlayer* byCharacter) {
	////UE_LOG(LogTemp, Warning, TEXT("(((( StopIsAimedAtForColor_Implementation"));
	Super::StopIsAimedAtForColor_Implementation(byCharacter);
	////UE_LOG(LogTemp, Warning, TEXT(")))) StopIsAimedAtForColor_Implementation"));
}

void AABBuildablePowerline::OnMaterialInstancesUpdated() {
	////UE_LOG(LogTemp, Warning, TEXT("(((( OnMaterialInstancesUpdated"));
	Super::OnMaterialInstancesUpdated();
	////UE_LOG(LogTemp, Warning, TEXT(")))) OnMaterialInstancesUpdated"));
}

void AABBuildablePowerline::OnSkinCustomizationApplied(TSubclassOf<class UFGFactoryCustomizationDescriptor_Skin> skin) {
	////UE_LOG(LogTemp, Warning, TEXT("(((( OnSkinCustomizationApplied"));
	Super::OnSkinCustomizationApplied(skin);
	////UE_LOG(LogTemp, Warning, TEXT(")))) OnSkinCustomizationApplied"));
}

void AABBuildablePowerline::ApplySkinData(TSubclassOf<UFGFactoryCustomizationDescriptor_Skin> newSkinDesc) {
	////UE_LOG(LogTemp, Warning, TEXT("(((( ApplySkinData"));
	Super::ApplySkinData(newSkinDesc);
	////UE_LOG(LogTemp, Warning, TEXT(")))) ApplySkinData"));
}

void AABBuildablePowerline::ApplyMeshPrimitiveData(const FFactoryCustomizationData& customizationData) {
	////UE_LOG(LogTemp, Warning, TEXT("(((( ApplyMeshPrimitiveData"));
	Super::ApplyMeshPrimitiveData(customizationData);
	////UE_LOG(LogTemp, Warning, TEXT(")))) ApplyMeshPrimitiveData"));
}

void AABBuildablePowerline::OnRep_CustomizationData() {
	////UE_LOG(LogTemp, Warning, TEXT("(((( OnRep_CustomizationData"));
	Super::OnRep_CustomizationData();
	////UE_LOG(LogTemp, Warning, TEXT(")))) OnRep_CustomizationData"));
}

void AABBuildablePowerline::ApplyCustomizationData_Implementation(const FFactoryCustomizationData& customizationData) {
	////UE_LOG(LogTemp, Warning, TEXT("(((( ApplyCustomizationData_Implementation"));
	Super::ApplyCustomizationData_Implementation(customizationData);
	////UE_LOG(LogTemp, Warning, TEXT(")))) ApplyCustomizationData_Implementation"));
}
void AABBuildablePowerline::SetCustomizationData_Implementation(const FFactoryCustomizationData& customizationData) {
	////UE_LOG(LogTemp, Warning, TEXT("(((( SetCustomizationData_Implementation"));
	Super::SetCustomizationData_Implementation(customizationData);
	////UE_LOG(LogTemp, Warning, TEXT(")))) SetCustomizationData_Implementation"));
}

void AABBuildablePowerline::OnRep_Connections() {
	////UE_LOG(LogTemp, Warning, TEXT("(((( OnRep_Connections"));
	Super::OnRep_Connections();
	////UE_LOG(LogTemp, Warning, TEXT(")))) OnRep_Connections"));
}

UStaticMeshComponent* AABBuildablePowerline::CreateNewWireMesh() {
	////UE_LOG(LogTemp, Warning, TEXT("(--) CreateNewWireMesh"));
	return Super::CreateNewWireMesh();
}

void AABBuildablePowerline::DestroyWireInstances() {
	////UE_LOG(LogTemp, Warning, TEXT("(((( DestroyWireInstances"));
	Super::DestroyWireInstances();
	////UE_LOG(LogTemp, Warning, TEXT(")))) DestroyWireInstances"));
}

void AABBuildablePowerline::UpdateWireMeshes() {
	////UE_LOG(LogTemp, Warning, TEXT("(((( UpdateWireMeshes"));
	Super::UpdateWireMeshes();
	////UE_LOG(LogTemp, Warning, TEXT(")))) UpdateWireMeshes"));
}

// ^^^ */