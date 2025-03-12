#include "PlayerBounce.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UPlayerBounce::UPlayerBounce()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPlayerBounce::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void UPlayerBounce::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerBounce::HandleBounce(AActor* OtherActor, const FVector& HitNormal, const FVector& MyVelocity, const FVector& OtherVelocity, const float& MyMass, const float& OtherMass)
{
    if (OtherActor)
    {
        // Get velocities of both objects
        FVector MyCurrentVelocity = MyVelocity;
        FVector OtherCurrentVelocity = OtherVelocity;

        // Calculate relative velocity
        FVector RelativeVelocity = MyCurrentVelocity - OtherCurrentVelocity;
        /*FString RelativeVelocityString = RelativeVelocity.ToString();
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, RelativeVelocityString);*/

        // Compute the impulse magnitude based on the collision
        float ImpulseMagnitude = FVector::DotProduct(RelativeVelocity, HitNormal) * (1 + Restitution);
        /*FString ImpulseString = FString::Printf(TEXT("Impulse: %.2f"), ImpulseMagnitude);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, ImpulseString);*/

        // Compute the reflected velocities using the reflection formula
        FVector MyReflectiveVelocity = MyCurrentVelocity - (2 * ImpulseMagnitude * HitNormal) * (OtherMass / (MyMass + OtherMass));
        /*FString MyCurrentVelocityString = MyCurrentVelocity.ToString();
        FString MyReflectiveVelocityString = MyReflectiveVelocity.ToString();
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "CurrentVel: " + MyCurrentVelocityString);*/

        // Apply the new velocity using LaunchCharacter
        ACharacter* MyCharacter = Cast<ACharacter>(GetOwner());
        if (MyCharacter)
        {
            // No need for the minus sign here
            FVector FinalLaunchVelocity = MyReflectiveVelocity;
            MyCharacter->LaunchCharacter(FinalLaunchVelocity, true, true);

            // Debugging
            /*FString VectorString = FinalLaunchVelocity.ToString();
            FString NormalString = HitNormal.ToString();
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Launch Vel: " + VectorString + " | Normal: " + NormalString);*/
        }
    }
}
