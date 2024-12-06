// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* TriggerActor = GetAcceptableActor();

    if(TriggerActor != nullptr)
    {
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(TriggerActor->GetRootComponent());
        if(Component != nullptr)
        {
            Component->SetSimulatePhysics(false);
        }
        TriggerActor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
        TriggerActor->SetActorRelativeRotation(FRotator::ZeroRotator);
        Mover->SetShouldMove(true);
    }
    else
    {
        Mover->SetShouldMove(false);
    }
}


void UTriggerComponent::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    for(AActor* Actor : Actors)
    {
        bool HasUnlockTag = Actor->ActorHasTag(UnlockTag);
        bool IsGrabbed = Actor->ActorHasTag("Grabbed");
        if(HasUnlockTag && !IsGrabbed)
        {
            return Actor;
        }
    }

    return nullptr;
}