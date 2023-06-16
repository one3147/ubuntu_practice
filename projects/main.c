int main() {
    SoftwareBlock blocks[MAX_BLOCKS];
    int blockCount;

    initializeSoftwareBlocks("software_blocks.txt", blocks, &blockCount);

    printf("Software Blocks:\n");
    for (int i = 0; i < blockCount; i++) {
        printf("Block Name: %s\n", blocks[i].name);
        printf("Parameters: ");
        for (int j = 0; j < blocks[i].paramCount; j++) {
            printf("%s ", blocks[i].params[j]);
        }
        printf("\n\n");
    }

    return 0;
}
