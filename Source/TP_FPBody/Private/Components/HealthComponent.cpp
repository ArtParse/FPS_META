// Copyright 2022 Ellie Kelemen. All Rights Reserved.


#include "Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	Health = DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		// Binding our handling function to the owner's OnTakeAnyDamage
        Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeAnyDamage);
 	}
}

void UHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;
	Health = FMath::Clamp(Health - Damage, 0.f, 100.f);
	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
}

void UHealthComponent::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageAmount <= 0.f) return;
	Health = FMath::Clamp(Health - DamageAmount, 0.f, 100.f);
	//OnHealthChanged.Broadcast(this, Health, DamageAmount, DamageType::StaticClass(), InstigatedBy, EventInstigator, DamageCauser);
}