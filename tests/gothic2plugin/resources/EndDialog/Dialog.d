INSTANCE DIA_Xardas_FirstEXIT (C_INFO) {
	npc			= Xardas;
	nr			= 1;
	condition	= DIA_Xardas_FirstEXIT_Condition;
	information	= DIA_Xardas_FirstEXIT_Info;
	permanent	= TRUE;
	important	= FALSE;
	description	= "Ich werde so schnell wie m�glich aufbrechen! (ENDE)";
};

FUNC INT DIA_Xardas_FirstEXIT_Condition() {
	return TRUE;
};

FUNC VOID DIA_Xardas_FirstEXIT_Info() {
	AI_Output (other, self, "DIA_Xardas_FirstEXIT_15_00"); //Ich werde so schnell wie m�glich aufbrechen!
	AI_Output (self, other, "DIA_Xardas_FirstEXIT_14_01"); //Gut! Und eines noch: Verrate niemandem, dass du mit mir gesprochen hast. Vor allem keinem Magier.
	AI_Output (self, other, "DIA_Xardas_FirstEXIT_14_02"); //Seit ich ins Exil gegangen bin, h�lt mich der Kreis des Feuers f�r tot, und das ist auch gut so.
	AI_StopProcessInfos (self);
};
