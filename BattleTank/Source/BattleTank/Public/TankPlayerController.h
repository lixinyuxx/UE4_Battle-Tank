// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    ATank* GetControlledTank() const;
    
    virtual void BeginPlay() override;
    
    virtual void Tick(float DeltaTime) override;

    //Start the Tank moving the barrel so that a shot would it where the crosshair
    void AimTowardsCrosshair();
    
    //Return an out Parameter,True if it hit landscape
    bool GetSightRayHitLocation(FVector& OutHitLocation) const;

};
