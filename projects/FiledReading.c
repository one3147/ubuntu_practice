void parseSoftwareBlocks(const char* filename, SoftwareBlock* blocks, int* blockCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    *blockCount = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (*blockCount >= MAX_BLOCKS) {
            printf("Maximum number of software blocks exceeded.\n");
            exit(1);
        }

        SoftwareBlock* block = &blocks[*blockCount];

        char* token = strtok(line, ";");
        strncpy(block->name, token, sizeof(block->name) - 1);
        block->name[sizeof(block->name) - 1] = '\0';

        block->paramCount = 0;
        token = strtok(NULL, ";");
        while (token != NULL && block->paramCount < MAX_PARAMS) {
            strncpy(block->params[block->paramCount], token, sizeof(block->params[block->paramCount]) - 1);
            block->params[block->paramCount][sizeof(block->params[block->paramCount]) - 1] = '\0';
            block->paramCount++;
            token = strtok(NULL, ";");
        }

        (*blockCount)++;
    }

    fclose(file);
}
