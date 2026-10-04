#pragma once

#include "NativeGameplayTags.h"

namespace RogueGameplayTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Health);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_HealthMax);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_PrimaryAttack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_SecondaryAttack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_SpecialAttack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Sprint);
}

/*
 * Quello che è stato fatto in questo file (e nel cpp) è la stessa identica procedura
 * di crear eun tag attraverso l'engine nella sezione gameplaytags nelle impostazioni 
 * del progetto.
 *  Qua viene mostrato come creare quasta macro in codice
 */