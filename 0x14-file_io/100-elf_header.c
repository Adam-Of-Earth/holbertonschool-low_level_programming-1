#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "holberton.h"


/**
 * is_elf - checks if header is the beginning of an ELF file
 * @header: at least first 4 bytes of a file
 *
 * Return: 1 if ELF file, 0 otherwise
 */
int is_elf(unsigned char const *header)
{
	unsigned char const check[] = {ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3};
	size_t i;

	for (i = 0; i < sizeof(check); i++)
	{
		if (header[i] != check[i])
			return (0);
	}
	return (1);
}


/**
 * print_magic2 - print the next bit of information in an ELF header
 * @h: buffer that stores ELF file header
 */
void print_magic2(unsigned char const *h)
{
	switch (h[EI_VERSION])
	{
	case EV_CURRENT:
		printf("  %-35s%hd (%s)\n", "Version:", h[EI_VERSION], "current");
		break;
	default:
		printf("  %-35s%hd (%s)\n", "Version:", h[EI_VERSION], "unknown");
	}
	switch (h[EI_OSABI])
	{
	case ELFOSABI_SYSV:
		printf("  %-35s%s\n", "OS/ABI:", "UNIX - System V");
		break;
	case ELFOSABI_NETBSD:
		printf("  %-35s%s\n", "OS/ABI:", "UNIX - NetBSD");
		break;
	case ELFOSABI_SOLARIS:
		printf("  %-35s%s\n", "OS/ABI:", "UNIX - Solaris");
		break;
	default:
		printf("  %-35s<unknown: %hd>\n", "OS/ABI:", h[EI_OSABI]);
	}
	printf("  %-35s%hd\n", "ABI Version:", h[EI_ABIVERSION]);
}


/**
 * print_magic - print the information in the magic array of an ELF file
 * @header: buffer that stores ELF file header
 */
void print_magic(unsigned char const *header)
{
	unsigned char i;

	if (header[EI_CLASS] != ELFCLASS32 && header[EI_CLASS] != ELFCLASS64)
	{
		dprintf(STDERR_FILENO, "Error: unknown ELF class\n");
		exit(98);
	}
	printf("ELF Header:\n  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x", header[i]);
		if (i < EI_NIDENT - 1)
			printf(" ");
	}
	printf("\n");
	switch (header[EI_CLASS])
	{
	case ELFCLASS32:
		printf("  %-35s%s\n", "Class:", "ELF32");
		break;
	case ELFCLASS64:
		printf("  %-35s%s\n", "Class:", "ELF64");
		break;
	default:
		printf("  %-35s%s\n", "Class:", "Invalid");
	}
	switch (header[EI_DATA])
	{
	case ELFDATA2LSB:
		printf("  %-35s%s\n", "Data:", "2's complement, little endian");
		break;
	case ELFDATA2MSB:
		printf("  %-35s%s\n", "Data:", "2's complement, big endian");
		break;
	default:
		printf("  %-35s%s\n", "Data:", "unknown");
	}
	print_magic2(header);
}


/**
 * print_type - print type of ELF file
 * @header: buffer containing ELF header
 */
void print_type(unsigned char const *header)
{
	switch (((Elf32_Ehdr *)header)->e_type)
	{
	case ET_REL:
		printf("  %-35s%s\n", "Type:", "REL (Relocatable file)");
		break;
	case ET_EXEC:
		printf("  %-35s%s\n", "Type:", "EXEC (Executable file)");
		break;
	case ET_DYN:
		printf("  %-35s%s\n", "Type:", "DYN (Shared object file)");
		break;
	case ET_CORE:
		printf("  %-35s%s\n", "Type:", "CORE (Core file)");
		break;
	default:
		printf("  %-35s%s\n", "Type:", "NONE (Unknown)");
	}
}


/**
 * print_entry - print entry point of ELF file
 * @header: buffer containing ELF header
 */
void print_entry(unsigned char const *header)
{
	uint64_t address;

	if (header[EI_CLASS] == ELFCLASS32)
		address = ((Elf32_Ehdr *)header)->e_entry;
	else if (header[EI_CLASS] == ELFCLASS64)
		address = ((Elf64_Ehdr *)header)->e_entry;
	printf("  %-35s%#lx\n", "Entry point address:", address);
}


/**
 * main - entry point, prints information about ELF files
 * @argc: number of command-line arguments
 * @argv: list of command-line arguments
 *
 * Return: error code
 */
int main(int argc, char *argv[])
{
	unsigned char buffer[sizeof(Elf64_Ehdr)] = {0};
	int file;
	ssize_t result;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: elf_header elf_filename\n");
		exit(98);
	}
	file = open(argv[1], O_RDONLY);
	if (file < 0)
	{
		dprintf(STDERR_FILENO, "Error: can't open file\n");
		exit(98);
	}
	result = read(file, buffer, sizeof(Elf64_Ehdr));
	if (result < 0 || (size_t)result < sizeof(Elf32_Ehdr))
	{
		dprintf(STDERR_FILENO, "Error: can't read header from file\n");
		exit(98);
	}
	if (!is_elf(buffer))
	{
		dprintf(STDERR_FILENO, "Error: not an ELF file\n");
		exit(98);
	}
	print_magic(buffer);
	print_type(buffer);
	print_entry(buffer);
	return (0);
}
