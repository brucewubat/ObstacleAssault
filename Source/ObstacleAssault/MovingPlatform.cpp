// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("MovingPaltform Begin!!!"));

    FVector StartPosition = GetActorLocation();
    OriginalPosition = StartPosition;
	SetActorLocation(StartPosition);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    RotationUpdate(DeltaTime);

    LocationUpdateByVelocity(DeltaTime);
}

void AMovingPlatform::LocationUpdate(float DeltaTime) 
{
    FVector CurPosition = GetActorLocation();

    // 使用DeltaTime保证速度与帧率无关
    if (IsForward)
    {
        CurPosition += MovingVelocity * DeltaTime;
    }
    else
    {
        CurPosition -= MovingVelocity * DeltaTime;
    }

    // 钳位，防止冲出去边界
    float NewDist = FVector::Dist(CurPosition, OriginalPosition);
    if (NewDist >= MaxDistance)
    {
        IsForward = false;
        FVector Dir = (CurPosition - OriginalPosition).GetSafeNormal();
        CurPosition = OriginalPosition + Dir * MaxDistance;
    }
    else if (NewDist <= MinDistance)
    {
        IsForward = true;
        FVector Dir = (CurPosition - OriginalPosition).GetSafeNormal();
        CurPosition = OriginalPosition + Dir * MinDistance;
    }

    SetActorLocation(CurPosition);

}

void AMovingPlatform::LocationUpdateByVelocity(float DeltaTime)
{
    FVector CurPosition = GetActorLocation();
    CurPosition += MovingVelocity * DeltaTime;
    SetActorLocation(CurPosition);
    MovingDistance = FVector::Dist(CurPosition, OriginalPosition);
    if (MovingDistance >= MaxDistance) 
    {
        FVector VelocityVector = MovingVelocity.GetSafeNormal();
        FVector NewPosition = OriginalPosition + VelocityVector * MaxDistance;
        SetActorLocation(NewPosition);
        OriginalPosition = NewPosition;
        MovingVelocity = -MovingVelocity;
    }
}

void AMovingPlatform::RotationUpdate(float DeltaTime)
{
    FRotator rotationToAdd = RotatingVelocity * DeltaTime;

    AddActorLocalRotation(rotationToAdd);
}

