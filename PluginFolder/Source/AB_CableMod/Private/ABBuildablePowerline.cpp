// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "ABBuildablePowerline.h"

// Satic init
//////////////////////////////////////////////////////


// Ctor
//////////////////////////////////////////////////////
AABBuildablePowerline::AABBuildablePowerline() {
	UE_LOG(LogTemp, Warning, TEXT("()()()()() I'M IN ()()()()()"));
}

// Factory interface
//////////////////////////////////////////////////////
void AABBuildablePowerline::SetCustomizationData_Implementation(const FFactoryCustomizationData& customizationData) {
	Super::SetCustomizationData_Implementation(customizationData);
	UE_LOG(LogTemp, Warning, TEXT("()()()()() SetCustomizationData_Implementation ()()()()()"));
}

void AABBuildablePowerline::SetCustomizationData_Native(const FFactoryCustomizationData& customizationData) {
	Super::SetCustomizationData_Native(customizationData);
	UE_LOG(LogTemp, Warning, TEXT("()()()()() SetCustomizationData_Native ()()()()()"));

	/*
    UStruct* pUVar1;
    AGameStateBase* pAVar2;
    AFGBuildableBlueprintDesigner* this_00;
    bool bVar3;
    int uVar4;
    UClass* pUVar5;
    UClass* pUVar6;
    AFGGameState* pAVar7;
    UWorld* pUVar8;
    TSubclassOf<UFGFactoryCustomizationDescriptor> TVar9;
    AFGGameState* gameState;
    int customizationID;

    //* 0x378e80  22956
    //   ?SetCustomizationData_Native@AFGBuildable@@UEAAXAEBUFFactoryCustomizationData @@@Z
    //    
    pUVar6 = (customizationData->SkinDesc).Class;
    TVar9.Class = NULL;
    gameState = (AFGGameState*)TVar9.Class;
    if (pUVar6 != NULL) {
        pUVar5 = UFGFactoryCustomizationDescriptor_Skin::GetPrivateStaticClass();
        if (pUVar6->IsChildOf((UStruct*)pUVar5)) {
            gameState = (AFGGameState*)(customizationData->SkinDesc).Class;
        }
    }

    pUVar1 = *(UStruct**)&this->field_0x100;
    pAVar7 = (AFGGameState*)TVar9.Class;
    if (pUVar1 != (UStruct*)0x0) {
        pUVar6 = UFGFactoryCustomizationDescriptor_Skin::GetPrivateStaticClass();
        if (pUVar1->IsChildOf((UStruct*)pUVar6)) {
            pAVar7 = *(AFGGameState**)&this->field_0x100;
        }
    }

    if (gameState != pAVar7) {
        this->field_0x159 = 1;
    }

    pUVar8 = GetWorld();
    gameState = (AFGGameState*)TVar9.Class;
    if ((pUVar8->GameState).field0_0x0.DebugPtr != NULL) {
        pUVar6 = AFGGameState::GetPrivateStaticClass();
        pAVar2 = (pUVar8->GameState).field0_0x0.DebugPtr;
        if (((pAVar2 != NULL) &&
            (pUVar1 = *(UStruct**)&pAVar2->field_0x10, pUVar1 != NULL)) &&
            (bVar3 = UStruct::IsChildOf(pUVar1, (UStruct*)pUVar6), bVar3)) {
            gameState = (AFGGameState*)(pUVar8->GameState).field0_0x0.DebugPtr;
        }
    }

    FFactoryCustomizationData::InlineCombine((FFactoryCustomizationData*)&this->field_0xe8, customizationData);
    FFactoryCustomizationData::Initialize((FFactoryCustomizationData*)&this->field_0xe8, gameState);
    pUVar6 = (customizationData->SwatchDesc).Class;
    if (pUVar6 != NULL) {
        pUVar5 = UFGFactoryCustomizationDescriptor_Swatch::GetPrivateStaticClass();
        if (pUVar6->IsChildOf((UStruct*)pUVar5)) {
            TVar9.Class = (param_1->SwatchDesc).Class;
        }
    }

    uVar4 = UFGBlueprintFunctionLibrary::GetIDForCustomizationDesc(TVar9);
    if (uVar4 != (byte)this->field_0xe0) {
        customizationID = 0;
        if (uVar4 - 1 < 0xff) {
            customizationID = (undefined)uVar4;
        }
        this->field_0xe0 = customizationID;
    }
     
    (**(code**)(*(longlong*)this + 0x70))(this, &this->field_0xe8);
    this_00 = *(AFGBuildableBlueprintDesigner**)&this->field_0x218;
    this->field_0x159 = 0;
    if ((this_00 != (AFGBuildableBlueprintDesigner*)0x0) &&
        ((*(uint*)&this_00->field_0x8 & 0x60000000) == 0)) {
        AFGBuildableBlueprintDesigner::OnBuildableChangedInsideDesigner
        (this_00, (AFGBuildable*)&this[-1].field_0x2c8);
    }
    // WARNING: Could not recover jumptable at 0x000180379010. Too many branches 
    // WARNING: Treating indirect jump as call 
    (**(code**)(*(longlong*)&this[-1].field_0x2c8 + 0x690))(&this[-1].field_0x2c8);
    return;
	//*/
}

void AABBuildablePowerline::ApplySkinData(TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > newSkinDesc) {
    Super::ApplySkinData(newSkinDesc);
    UE_LOG(LogTemp, Warning, TEXT("()()()()() ApplySkinData ()()()()()"));
}