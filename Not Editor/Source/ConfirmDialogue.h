#pragma once
#include "EditorComponents.h"
#include "MiscStructs.h"


class ConfirmDialogue : public EditorComponents
{
private:
	bool mStatus;
	const char* mMessage;
public:
	ConfirmDialogue(NotEditor* Parent);
	~ConfirmDialogue();

	inline void SetMessage(const char* NewMessage) { mMessage = NewMessage; }
	inline bool GetStatus() { bool retVal = mStatus; mStatus &= false; return retVal; }

	void Ready() override;
	void Render() override;
};
