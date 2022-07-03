#ifndef GENE_H
#define GENE_H

class Gene
{
public:
	Gene(int coordinate, int index, bool rotate = false);

	int get_coordinate() const;
	int get_index() const;
	bool get_rotation() const;
protected:
	int coordinate_;
	int index_;
	bool rotate_;
};

#endif
