// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    bWantsBeginPlay = true;
    PrimaryComponentTick.bCanEverTick = true;
    // ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
    /*auto OurTankName = GetOwner()->GetName();
    //UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *HitLocation.ToString());
    auto BarrelLocation = Barrel->GetComponentLocation().ToString();
    UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation);
     */
    //UE_LOG(LogTemp, Warning, TEXT("Firing at %f"), LaunchSpeed);
    if (!Barrel) { return; }

    FVector OutLaunchVelocity(0);
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    /*if (UGameplayStatics::SuggestProjectileVelocity
        (
            this,
            OutLaunchVelocity,
            StartLocation,
            HitLocation,
            LaunchSpeed,
            false,
            0,
            0,
            ESuggestProjVelocityTraceOption::DoNotTrace
            )
        )
     */
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
    (
        this,
        OutLaunchVelocity,
        StartLocation,
        HitLocation,
        LaunchSpeed,
        ESuggestProjVelocityTraceOption::DoNotTrace
    );
    if (bHaveAimSolution)
    {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        //UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
        MoveBarrelTowards(AimDirection);
    }
    // If no solution found do nothing
}
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    // Work-out difference between current barrel roation, and AimDirection
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    //UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());
    
    Barrel->Elevate(5); // TODO remove magic number
    
}
