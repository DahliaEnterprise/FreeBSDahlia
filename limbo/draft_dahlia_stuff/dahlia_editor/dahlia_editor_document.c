void dahlia_editor_document_initialize(){
	dahlia_editor_wholeDocumentContents = 0;
	while( dahlia_editor_wholeDocumentContents == 0 ){ dahlia_editor_wholeDocumentContents = (char*)malloc(1024 * sizeof(char)); } memset(dahlia_editor_wholeDocumentContents, '\0', 1024);
	dahlia_editor_wholeDocumentContents_memory_size = 1024;
	dahlia_editor_wholeDocumentContents_cursor_index = 0;
}

void dahlia_editor_document_insert_string(char* stringToInsert){
	uint32_t stringToInsert_string_length = strlen(stringToInsert);
	uint32_t wholeDocumentContents_startIndex = dahlia_editor_wholeDocumentContents_cursor_index;
	uint32_t wholeDocumentContents_endIndex = wholeDocumentContents_startIndex + stringToInsert_string_length;
	uint32_t wholeDocumentContents_currentIndex = wholeDocumentContents_startIndex;
	uint32_t stringToInsert_currentIndex = 0;
	while(wholeDocumentContents_currentIndex < wholeDocumentContents_endIndex){
		dahlia_editor_wholeDocumentContents[wholeDocumentContents_currentIndex] = stringToInsert[stringToInsert_currentIndex];
		
		//Next.
		wholeDocumentContents_currentIndex = wholeDocumentContents_currentIndex + 1;
			//Increase Cursor Index as letters are inserted.
			dahlia_editor_wholeDocumentContents_cursor_index = dahlia_editor_wholeDocumentContents_cursor_index + 1;
	}
	printf("%s\n", dahlia_editor_wholeDocumentContents);
}
