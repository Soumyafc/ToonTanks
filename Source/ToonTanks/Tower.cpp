// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Find the distance to the Tank
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

        // Check to see if the Tank is in range
        if (Distance <= FireRange)
        {
            // If in range, rotate turret toward Tank
            RotateTurret(Tank->GetActorLocation());
        }
    }
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(   //Setting timer for fire
        FireRateTimerHandle, 
        this, 
        &ATower::CheckFireCondition,
        FireTimer,
        true
    );
}

void ATower::CheckFireCondition()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

        // Check to see if the Tank is in range
        if (Distance <= FireRange)
        {
            Fire();
        }
    }
}
