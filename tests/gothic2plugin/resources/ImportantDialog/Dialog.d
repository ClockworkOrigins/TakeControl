INSTANCE DIA_Xardas_Hello (C_INFO) {
	npc			= Xardas;
	nr			= 1;
	condition	= DIA_Xardas_Hello_Condition;
	information	= DIA_Xardas_Hello_Info;
	permanent	= FALSE;
	important	= TRUE;
};

FUNC INT DIA_Xardas_Hello_Condition() {
	return TRUE;
};

FUNC VOID DIA_Xardas_Hello_Info() {
	AI_Output (self, other, "DIA_Addon_Xardas_Hello_14_00"); //Da bist du ja wieder! (schmunzelt) Ich h�tte nicht gedacht, da� wir uns nochmal wiedersehen.
	AI_Output (other, self, "DIA_Addon_Xardas_Hello_15_01"); //Ich f�hle mich, als h�tte ich drei Wochen unter Steinen gelegen.
	AI_Output (self, other, "DIA_Addon_Xardas_Hello_14_02"); //So war es auch. Nur die Magie deiner R�stung hat dich am Leben gehalten 
	AI_Output (self, other, "DIA_Addon_Xardas_Hello_14_03"); //Ich hatte schon bef�rchtet, dich nicht mehr aus den Tr�mmern des Tempels befreien zu k�nnen.
	AI_Output (self, other, "DIA_Addon_Xardas_Hello_14_04"); //Aber genug davon. Jetzt bist du ja hier.
	AI_Output (self, other, "DIA_Addon_Xardas_Hello_14_05"); //Es gibt eine NEUE Bedrohung, um die wir uns k�mmern m�ssen.
};
