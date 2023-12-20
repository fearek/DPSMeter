#include "pch.h"
#include ".\UI\DX Input.h"


bool DXInput::Init(HINSTANCE hinst, HWND hWnd) {
	
	HRESULT result = DirectInput8Create(hinst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_directInput, NULL);

	if (FAILED(result)) {
		LogInstance.WriteLog("Error in DirectInput8Create");
		return false;
	}
	

	if (FAILED(_directInput->CreateDevice(GUID_SysKeyboard, &_keyboard, NULL))) {
		LogInstance.WriteLog("Error in CreateDevice");
		return false;
	}

	if (FAILED(_keyboard->SetDataFormat(&c_dfDIKeyboard))) {
		LogInstance.WriteLog("Error in SetDataFormat");
		return false;
	}

	if (FAILED(_keyboard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {
		LogInstance.WriteLog("Error in SetCooperativeLevel");
		return false;
	}

	if (FAILED(_keyboard->Acquire())) {
		LogInstance.WriteLog("Error in Acquire");
		return false;
	}

	return true;
}

void DXInput::Shutdown() {

	if (_keyboard != nullptr) {
		_keyboard->Unacquire();
		_keyboard->Release();
		_keyboard = nullptr;
	}

	if (_directInput != nullptr) {
		_directInput->Release(); 
		_directInput = nullptr;
	}

}

bool DXInput::Update() {

	HRESULT result = _keyboard->GetDeviceState(sizeof(_keyboardState), (void*)&_keyboardState);

	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	for (int i = 0; i < 256; i++) {
		_inputInfo[i].Update(_keyboardState[i] & 0x80 ? true : false);
	}

	return true;
}

bool DXInput::isKeyDown(unsigned int i) {
	
	if (i >= 0 && i < GetStateSize())
		return _inputInfo[i].isDown();
	else
		return false;
}

bool DXInput::isKeyRelease(unsigned int i) {

	if (i >= 0 && i < GetStateSize())
		return _inputInfo[i].isRelease();
	else
		return false;
}

bool DXInput::isKeyPressed(unsigned int i) {

	if (i >= 0 && i < GetStateSize())
		return _inputInfo[i].isPress();
	else
		return false;
}

bool DXInput::isKeyIdle(unsigned int i) {
	if (i >= 0 && i < GetStateSize())
		return _inputInfo[i].isIdle();
	else
		return false;
}

unsigned int DXInput::GetStateSize() {
	return 256;
}