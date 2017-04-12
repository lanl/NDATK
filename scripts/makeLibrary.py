
"""
This script will create the initial library file to be used in NDATK.
"""

import argparse
import textwrap
import os
import time

import pyMCNP.xsdir


def libHeader(args):
    """
    libheader will create the header of the library file; everything up to (but
    not includeing) the 'ids' keyword.
    """
    header = textwrap.dedent("""
        type: {libtype}

        name: {name}

        provenance:
        File originally created by {user} on {date}
        %%
        """.format(
            libtype=args.type,
            name=args.name,
            user=os.getlogin(),
            date=time.ctime()),
    )

    return header


if __name__ == "__main__":
    print("\nI'm making a new library.")

    parser = argparse.ArgumentParser(description="Make a library for NDATK")
    requiredArgs = parser.add_argument_group("Required arguments:")
    requiredArgs.add_argument("name", type=str,
                              help="The name of the library")
    parser.add_argument("--type", type=str, default="ndatk_library_1.0",
                        help="The type of library file.")
    entryArgs = parser.add_mutually_exclusive_group(required=True)
    entryArgs.add_argument("--entries", type=str,
                           help="Path to file with xsdir entries on it")
    entryArgs.add_argument("--xsdir", type=str,
                           help="Path to full xsdir file")
    entryArgs.add_argument("--files", nargs="+")



    args = parser.parse_args()

    print("\nCreating an NDATK library file for library: {}".format(args.name))

    header = libHeader(args)
    print("-"*80,
          header,
          "-"*80)

    # Get list of ZAIDs and filenames
    ZA_files = {}
    if args.entries:
        pass
    elif args.xsdir:
        pass
    elif args.files:
        pass
