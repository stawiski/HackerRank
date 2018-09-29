#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 6
//#define DEBUG

#ifdef DEBUG
	#define IF_DEBUG(x)		(x);
#else
	#define IF_DEBUG(x)
#endif

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

int towns_count;
typedef struct town town;
town* towns;

void print_all_packages(town t)
{
	/* Print town's name. */
	printf("%s:\r\n", t.name);
	/* Iterate through town's post offices. */
	for (int o = 0; o < t.offices_count; o++) {
		/* Print post office id. */
		printf("\t%d:\r\n", o);
		/* Iterate through post office's packages. */
		for (int p = 0; p < t.offices[o].packages_count; p++) {
			printf("\t\t%s\r\n", t.offices[o].packages[p].id);
		}
	}
}

#ifdef DEBUG
void print_all(void)
{
	printf(" ### print all being ###\r\n");
	printf("towns_count = %d\r\n", towns_count);
	for (int t = 0; t < towns_count; t++) {
		/* Print town's name. */
		printf("Town: %s (offices_count = %d)\r\n", towns[t].name, towns[t].offices_count);
		/* Iterate through town's post offices. */
		for (int o = 0; o < towns[t].offices_count; o++) {
			/* Print post office id. */
			printf("\tOffice: %d (packages_count = %d):\r\n", o, towns[t].offices[o].packages_count);
			/* Iterate through post office's packages. */
			for (int p = 0; p < towns[t].offices[o].packages_count; p++) {
				printf("\t\tid = %s, weight = %d\r\n", towns[t].offices[o].packages[p].id, towns[t].offices[o].packages[p].weight);
			}
		}
	}
	printf(" ### print all end ###\r\n");
}

void print_office_packages(const int post_office_index, const post_office *o)
{
	/* Print post office id. */
	printf("\tOffice %d packages:\r\n", post_office_index);
	/* Iterate through post office's packages. */
	for (int p = 0; p < o->packages_count; p++) {
		printf("\t\t%s\r\n", o->packages[p].id);
	}
}
#endif

/*
	send_all_acceptable_packages:
	Sometimes two post offices, even in different towns, may organize the following transaction:
	the first one sends all its packages to the second one.
	The second one accepts the packages that satisfy the weight condition for the second office and rejects all other ones.
	These rejected packages return to the first office back and are stored in the same order they were stored before they were sent.
	The accepted packages move to the tail of the second office's queue in the same order they were stored in the first office.
*/
void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index)
{
	void *vptr = NULL;

	/* Check if source and target post office are the same. */
	if ((source == target) && (source_office_index == target_office_index)) {
		return;
	}

	/* Check if index is positive or zero. */
	if ((source_office_index < 0) || (target_office_index < 0)) {
		return;
	}

	/* Check if index is in range. */
	if ((source_office_index >= source->offices_count) || (target_office_index >= target->offices_count)) {
		return;
	}

	#ifdef DEBUG
		printf("\r\n ####################### \r\n");
		printf("%s()\r\n", __FUNCTION__));
		printf("source town: %s, source office: %d\r\n", source->name, source_office_index));
		printf("target town: %s, target office: %d\r\n", target->name, target_office_index);

		print_office_packages(source_office_index, &source->offices[source_office_index]);
		print_office_packages(target_office_index, &target->offices[target_office_index]);

		print_all();
	#endif
	
	/* Initialize accepted packages counter. */
	int acceptablePackagesCount = 0;
	/* Iterate through source post office packages. */
	for (int p = 0; p < source->offices[source_office_index].packages_count; p++) {
		/* If current package "p" satisfies target post office weight... */
		if (source->offices[source_office_index].packages[p].weight <= target->offices[target_office_index].max_weight && \
			source->offices[source_office_index].packages[p].weight >= target->offices[target_office_index].min_weight) {
			/* Count the number of accepted packages. */
			acceptablePackagesCount++;
		}
	}

	IF_DEBUG(printf("acceptablePackagesCount = %d\r\n", acceptablePackagesCount));

	/* If there are no packages to process, return. */
	if (acceptablePackagesCount == 0) {
		return;
	}

	/* Realloc target office packages (increase memory by the amount of new packages). */
	vptr = realloc(target->offices[target_office_index].packages, sizeof(package) * (target->offices[target_office_index].packages_count + acceptablePackagesCount));
	/* Check realloc result. */
	if (vptr == NULL) {
		printf("ERROR: realloc() failed to increase memory.\r\n");
		exit(-1);
	} else {
		target->offices[target_office_index].packages = vptr;
	}

	/* Initialize source head: pointer to first package. */
	package* source_head = &source->offices[source_office_index].packages[0];
	/* Initialize target tail: pointer to empty queue location in the target office package queue. */
	package* target_tail = &target->offices[target_office_index].packages[target->offices[target_office_index].packages_count];

	#ifdef DEBUG
		printf("source office packages_count = %d\r\n", source->offices[source_office_index].packages_count);
		printf("target office packages_count = %d\r\n", target->offices[target_office_index].packages_count);
		printf("Iterating through source post office packages...\r\n");
	#endif

	/* Iterate through source post office packages. */
	for (int p = 0; p < source->offices[source_office_index].packages_count; p++) {
		/* If current package "p" satisfies target post office weight... */
		if (source->offices[source_office_index].packages[p].weight <= target->offices[target_office_index].max_weight && \
			source->offices[source_office_index].packages[p].weight >= target->offices[target_office_index].min_weight) {
			IF_DEBUG(printf("\tpackage accepted: %s\r\n", source->offices[source_office_index].packages[p].id));
			/* We are sending the package from source to target. */
			/* Make the pointer in target office point to source office package. */
			*target_tail = source->offices[source_office_index].packages[p];
			/* Increase target package tail pointer: point to next free package location. */
			target_tail++;
		} else {
		/* Package "p" was not accepted into target post office. */
			/* We might need to requeue the package in source. */
			/* If head pointer is not pointing to a currently processed package. */
			if (source_head != &source->offices[source_office_index].packages[p]) {
				IF_DEBUG(printf("\tpackage requeued: %s\r\n", source->offices[source_office_index].packages[p].id));
				/* Make the pointer in source package queue point to head package. */
				*source_head = source->offices[source_office_index].packages[p];
				/* Increase head pointer. */
				source_head++;
			} else {
			/* Program will get here only if first package from the source is not accepted: but it does not need to be requeued. */
				IF_DEBUG(printf("\tpackage not requeued: %s\r\n", source->offices[source_office_index].packages[p].id));
				/* Increase head pointer. */
				source_head++;
			}
		}
	}

	/* If all packages were sent, free memory. */
	if (source->offices[source_office_index].packages_count == acceptablePackagesCount) {
		free(source->offices[source_office_index].packages);
	} else {
		/* Realloc source office packages (shrink memory by amount of accepted packages). */
		vptr = realloc(source->offices[source_office_index].packages, sizeof(package) * (source->offices[source_office_index].packages_count - acceptablePackagesCount));
		if (vptr == NULL) {
			printf("ERROR: realloc() failed to shrink memory.\r\n");
			exit(-1);
		} else {
			source->offices[source_office_index].packages = vptr;
		}
	}

	/* Fix packages counters. */
	target->offices[target_office_index].packages_count += acceptablePackagesCount;
	source->offices[source_office_index].packages_count -= acceptablePackagesCount;

	#ifdef DEBUG
		printf("Fixed package count.\r\n"));
		printf("source office packages_count = %d\r\n", source->offices[source_office_index].packages_count);
		printf("target office packages_count = %d\r\n", target->offices[target_office_index].packages_count);
		print_office_packages(source_office_index, &source->offices[source_office_index]);
		print_office_packages(target_office_index, &target->offices[target_office_index]);
		print_all();
		IF_DEBUG(printf("\r\n ####################### \r\n"));
	#endif
}

town town_with_most_packages(town* towns, int towns_count)
{
	/* Initialize the highest number of packages found. */
	int packagesMax = 0;
	/* Initialize town with most packages index. */
	int townMostPackagesIndex = 0;

	if (towns == NULL || towns_count == 0) {
		/* Error. */
		town err;
		return err;
	}

	/* Iterate through towns. */
	for (int t = 0; t < towns_count; t++) {
		/* Initialize the number of packages for this town. */
		int packagesCount = 0;
		/* Iterate through town's post offices. */
		for (int o = 0; o < towns[t].offices_count; o++) {
			/* Increase the number of packages for this town. */
			packagesCount += towns[t].offices[o].packages_count;
		}
		/* Check if this town's packages trump the last maximum. */
		if (packagesCount > packagesMax) {
			/* Overwrite with new town. */
			townMostPackagesIndex = t;
			packagesMax = packagesCount;
		}
	}

	return towns[townMostPackagesIndex];
}

town* find_town(town* towns, int towns_count, char* name)
{
	if (towns == NULL || towns_count == 0 || name == NULL) {
		/* Error. */
		return NULL;
	}
	
	/* Iterate through towns. */
	for (int t = 0; t < towns_count; t++) {
		/* Check if town's name matches. */
		if (strcmp(towns[t].name, name) == 0) {
			/* Return pointer to current town. */
			return &towns[t];
		}
	}
	
	/* Town not found. */
	return NULL;
}

void freeTowns(town* towns)
{
	/* Iterate through towns. */
	for (int t = 0; t < towns_count; t++) {
		/* Iterate through town's post offices. */
		for (int o = 0; o < towns[t].offices_count; o++) {
			/* Iterate through office's packages. */
			for (int p = 0; p < towns[t].offices[o].packages_count; p++) {
				/* Free package id. */
				free(towns[t].offices[o].packages[p].id);
			}
			/* Free packages. */
			free(towns[t].offices[o].packages);
		}
		/* Free offices. */
		free(towns[t].offices);
		/* Free town's name. */
		free(towns[t].name);
	}
	/* Free towns. */
	free(towns);
}

int main()
{
	scanf("%d", &towns_count);
	towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	/* Cleanup. */
	freeTowns(towns);
	return 0;
}
