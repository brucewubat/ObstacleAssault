// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FVector MovingVelocity = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere)
	float MaxDistance = 300.0f;
	UPROPERTY(EditAnywhere)
	float MinDistance = 0.0f;

	UPROPERTY(VisibleAnywhere)
	float MovingDistance = 0.0f;

	bool IsForward = true;

	UPROPERTY(EditAnywhere)
	FVector OriginalPosition = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere)
	FRotator RotatingVelocity;

	void LocationUpdate(float DeltaTime);
	void LocationUpdateByVelocity(float DeltaTime);
	void RotationUpdate(float DeltaTime);

};
