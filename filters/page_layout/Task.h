/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C) 2007-2008  Joseph Artsimovich <joseph_a@mail.ru>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PAGE_LAYOUT_TASK_H_
#define PAGE_LAYOUT_TASK_H_

#include "NonCopyable.h"
#include "RefCountable.h"
#include "FilterResult.h"
#include "PageId.h"
#include <QSizeF>

class TaskStatus;
class FilterData;
class DebugImages;
class ImageTransformation;
class QRectF;

namespace page_layout
{

class Filter;
class Settings;

class Task : public RefCountable
{
	DECLARE_NON_COPYABLE(Task)
public:
	Task(IntrusivePtr<Filter> const& filter,
		IntrusivePtr<Settings> const& settings,
		PageId const& page_id, QSizeF const& aggregated_content_size_mm,
		bool batch, bool debug);
	
	virtual ~Task();
	
	FilterResultPtr process(
		TaskStatus const& status, FilterData const& data,
		QRectF const& content_rect);
private:
	class UiUpdater;
	
	static QSizeF calcContentSizeMM(
		ImageTransformation const& xform, QRectF const& content_rect);
	
	IntrusivePtr<Filter> m_ptrFilter;
	IntrusivePtr<Settings> m_ptrSettings;
	//std::auto_ptr<DebugImages> m_ptrDbg;
	PageId m_pageId;
	QSizeF m_aggregatedContentSizeMM;
	bool m_batchProcessing;
};

} // namespace page_layout

#endif