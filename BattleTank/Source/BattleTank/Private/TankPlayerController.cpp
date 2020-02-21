// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
    //UE_LOG(LogTemp,Warning,TEXT("Player Controller Ticking!"));

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
    
    FVector OutHitLocation;//out Parameter
    if(GetSightRayHitLocation(OutHitLocation))//"Side-affect",is going to line trace,doesn't changeing anything
    {
    //UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *OutHitLocation.ToString());
        GetControlledTank()->AimAt(OutHitLocation);
        
    }
    
}
//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    int32 ViewportSizeX , ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation , ViewportSizeY * CrosshairXLocation);
    //UE_LOG(LogTemp,Warning,TEXT("ScreenLocation : %s"), *ScreenLocation.ToString());
    
    //Crosshair posisiton
    //"De-project" the screen position of the crosshair to a world direction,Line-trace along that look direction ,see what we end up hitting
    
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        // Line-trace along that LookDirection, and see what we hit (up to max range)
        GetLookVectorHitLocation(LookDirection, OutHitLocation);
    }
    
    return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    if (GetWorld()->LineTraceSingleByChannel(
            HitResult,
            StartLocation,
            EndLocation,
            ECollisionChannel::ECC_Visibility)
        )
    {
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false; // Line trace didn't succeed
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; // To be discarded
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        LookDirection
    );
}
