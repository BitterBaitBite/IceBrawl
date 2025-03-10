// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerBounce.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ICEBRAWL_API UPlayerBounce : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UPlayerBounce();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Bounce functionality
    UFUNCTION(BlueprintCallable)
    void HandleBounce(AActor* OtherActor, const FVector& HitNormal, const FVector& MyVelocity, const FVector& OtherVelocity, const float& MyMass, const float& OtherMass);

    // Coefficient of restitution (bounciness factor)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Restitution = 1.0f; // 1.0 for fully elastic collision, 0 for inelastic
};
