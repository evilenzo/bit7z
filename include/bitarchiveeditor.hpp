/*
 * bit7z - A C++ static library to interface with the 7-zip DLLs.
 * Copyright (c) 2014-2021  Riccardo Ostani - All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * Bit7z is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with bit7z; if not, see https://www.gnu.org/licenses/.
 */

#ifndef BITARCHIVEEDITOR_HPP
#define BITARCHIVEEDITOR_HPP

#include <unordered_map>

#include "bitarchivewriter.hpp"
#include "bittypes.hpp"

namespace bit7z {
    using std::vector;

    using EditedItems = std::unordered_map< uint32_t, BitItemsVector::value_type >;

    class BitArchiveEditor : public BitArchiveWriter {
        public:
            BitArchiveEditor( const Bit7zLibrary& lib,
                              const tstring& in_file,
                              const BitInOutFormat& format,
                              const tstring& password = TSTRING( "" ) );

            BitArchiveEditor( const BitArchiveEditor& ) = delete;

            BitArchiveEditor( BitArchiveEditor&& ) = delete;

            BitArchiveEditor& operator=( const BitArchiveEditor& ) = delete;

            BitArchiveEditor& operator=( BitArchiveEditor&& ) = delete;

            ~BitArchiveEditor() override;

            void setUpdateMode( UpdateMode update_mode ) override;

            void renameItem( uint32_t index, const tstring& new_path );

            void renameItem( const tstring& old_path, const tstring& new_path );

            void updateItem( uint32_t index, const tstring& in_file );

            void updateItem( uint32_t index, const vector< byte_t >& in_buffer );

            void updateItem( uint32_t index, istream& in_stream );

            void updateItem( const tstring& item_path, const tstring& in_file );

            void updateItem( const tstring& item_path, const vector< byte_t >& in_buffer );

            void updateItem( const tstring& item_path, istream& in_stream );

            void deleteItem( uint32_t index );

            void deleteItem( const tstring& item_path );

            void applyChanges();

        private:
            EditedItems mEditedItems;

            uint32_t findItem( const tstring& item_path );

            void checkIndex( uint32_t index );

            BitPropVariant getItemProperty( input_index index, BitProperty propID ) const override;

            HRESULT getItemStream( input_index index, ISequentialInStream** inStream ) const override;

            bool hasNewData( uint32_t index ) const noexcept override;

            bool hasNewProperties( uint32_t index ) const noexcept override;
    };
}

#endif //BITARCHIVEEDITOR_HPP