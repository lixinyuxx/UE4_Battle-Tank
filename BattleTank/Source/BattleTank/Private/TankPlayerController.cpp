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
}
