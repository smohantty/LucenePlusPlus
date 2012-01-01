/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#include "LuceneInc.h"
#include "CharBlockPool.h"
#include "DocumentsWriter.h"

namespace Lucene
{
    CharBlockPool::CharBlockPool(DocumentsWriterPtr docWriter)
    {
        numBuffer = 0;
        bufferUpto = -1;
        charUpto = DocumentsWriter::CHAR_BLOCK_SIZE;
        charOffset = -DocumentsWriter::CHAR_BLOCK_SIZE;
        buffers = CollectionCollection<CharArray>::newInstance(10);
        this->docWriter = docWriter;
    }

    CharBlockPool::~CharBlockPool()
    {
    }

    void CharBlockPool::reset()
    {
        docWriter->recycleCharBlocks(buffers, 1 + bufferUpto);
        bufferUpto = -1;
        charUpto = DocumentsWriter::CHAR_BLOCK_SIZE;
        charOffset = -DocumentsWriter::CHAR_BLOCK_SIZE;
    }

    void CharBlockPool::nextBuffer()
    {
        if (1 + bufferUpto == buffers.size())
            buffers.resize((int32_t)((double)buffers.size() * 1.5));
        docWriter->getCharBlock();
        buffer = buffers[1 + bufferUpto];
        ++bufferUpto;

        charUpto = 0;
        charOffset += DocumentsWriter::CHAR_BLOCK_SIZE;
    }
}
