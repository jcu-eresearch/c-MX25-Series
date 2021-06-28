# c-MX25-Series
c-MX25-Series is an C Library for the Macronix c-MX25-Series flash chip.
Tested with the MX25R6435F.

See https://github.com/jcu-eresearch/Arduino-MX25-Series for usage examples.

# Platform Specific Functions
To use this library, the following platform specific functions need to be implemented:

* `MX25Series___issue_command`
* `MX25Series___read`
* `MX25Series___write`
* `MX25Series___enable_cs_pin`
* `MX25Series___enable_reset_pin`
* `MX25Series___enable_write_protect_pin`
* `MX25Series___test_linker`

An example of these [function](https://github.com/jcu-eresearch/Arduino-MX25-Series/blob/master/src/library_functions.cpp).