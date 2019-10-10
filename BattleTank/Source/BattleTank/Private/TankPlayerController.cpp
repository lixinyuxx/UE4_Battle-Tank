// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
    UE_LOG(LogTemp,Warning,TEXT("Player Controller Ticking!"));

}




void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    auto ControlledTank = GetControlledTank();
    if(!ControlledTank)
    {
        UE_LOG(LogTemp,Warning,TEXT("PlayerController not possesing a tank"));

    }else{
        UE_LOG(LogTemp,Warning,TEXT("PlayerController possesing %s"),*(ControlledTank->GetName()));
    }
    UE_LOG(LogTemp,Warning,TEXT("PlayerController Begin Play"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
   return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetControlledTank())
    {
        return;
    }
    //Get World Location if Linetrace through crosshair
    //if it hits the landscape tell controlled tank to aim at this point
    
    FVector HitLocation;//out Parameter
    if(GetSightRayHitLocation(HitLocation))//"Side-affect",is going to line trace
    {
    UE_LOG(LogTemp,Warning,TEXT("HitLocation : %s"),*(HitLocation.ToString()));
    }
    
}
//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    OutHitLocation = FVector(1.0);
    return true;
}
