package com.example.arduinocontroller;

public class SerialCommand {
	/**
	//---------- buffer structure when received
	mDataArray[0] : a
	mDataArray[1] : 1
	mDataArray[2] : 2
	mDataArray[3] : .
	mDataArray[4] : 3
	mDataArray[5] : 4
	...
	mDataArray[n] : z
	
	==> converts into float number : 12.34xxxxxx
	 */
	
	
	public static final int SIZE_IN_BYTE = 20;
	public StringBuilder mStringBuffer;

	
	public SerialCommand() {
	}
	
	public void initialize() {
		mStringBuffer = new StringBuilder();
	}
	
	public void addChar(char c) {
		if(c == 'a') {
			initialize();
		} else {
			mStringBuffer.append(c);
		}
	}
	
	public String toString() {
		return mStringBuffer.length()>0 ? mStringBuffer.toString() : "No data";
	}
}
