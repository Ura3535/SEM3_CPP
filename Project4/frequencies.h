#pragma once

namespace frequencies
{
	struct Frequencies
	{
		int sum() const
		{
			return field_0_read + field_0_write
				+ field_1_read + field_1_write
				+ field_2_read + field_2_write
				+ string;
		}

		const int
			field_0_read,
			field_0_write,
			field_1_read,
			field_1_write,
			field_2_read,
			field_2_write,
			string;
	};

	const Frequencies variant_12{ 20, 5, 20, 5, 10, 20, 20 };
	const Frequencies equal{ 1, 1, 1, 1, 1, 1, 1 };
	const Frequencies my_freq{ 1, 1, 2, 4, 8, 16, 32 };
}