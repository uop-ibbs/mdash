/////////////////////////////////////////////////////////////////////////////
// Name:	dataset.cpp
// Purpose: dataset implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// Copyright:	(c) 2008-2010 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/dataset.h>

#include <algorithm>

DatasetObserver::DatasetObserver()
{
}

DatasetObserver::~DatasetObserver()
{
}

//
// Dataset
//

IMPLEMENT_CLASS(Dataset, wxObject)

Dataset::Dataset()
{
	m_renderer = NULL;
	m_updating = false;
	m_changed = false;
}

Dataset::~Dataset()
{
	for (size_t n = 0; n < m_markers.Count(); n++) {
		Marker *marker = m_markers[n];
		marker->RemoveObserver(this);
		wxDELETE(marker);
	}

	SAFE_UNREF(m_renderer);
}

void Dataset::SetRenderer(Renderer *renderer)
{
	SAFE_REPLACE_OBSERVER(this, m_renderer, renderer);
	SAFE_REPLACE_UNREF(m_renderer, renderer);
	DatasetChanged();
}

Renderer *Dataset::GetBaseRenderer()
{
	return m_renderer;
}

void Dataset::NeedRedraw(DrawObject *WXUNUSED(obj))
{
	DatasetChanged();
}

void Dataset::BeginUpdate()
{
	m_updating = true;
}

void Dataset::EndUpdate()
{
	if (m_updating) {
		m_updating = false;
		FireDatasetChanged();
	}
}

void Dataset::DatasetChanged()
{
	if (m_updating) {
		m_changed = true;
	}
	else {
		if (m_changed) {
			FireDatasetChanged();
		}
		m_changed = false;
	}
}

void Dataset::AddMarker(Marker *marker)
{
	marker->AddObserver(this);
	m_markers.Add(marker);
}

size_t Dataset::GetMarkersCount()
{
	return m_markers.Count();
}

Marker *Dataset::GetMarker(size_t index)
{
	return m_markers[index];
}

DateTimeDataset *Dataset::AsDateTimeDataset()
{
	return NULL; // dataset not supports date/times by default.
}

//
// DateTimeDataset
//

DateTimeDataset::DateTimeDataset()
{
}

DateTimeDataset::~DateTimeDataset()
{
}

//
// DatasetArray
//

DatasetArray::DatasetArray()
{
}

DatasetArray::~DatasetArray()
{
        for (Dataset* dataset: m_datasetarray) {
            SAFE_UNREF(dataset);
        }
}

void DatasetArray::Add(Dataset *dataset)
{
	dataset->AddRef();
        m_datasetarray.push_back(dataset);
}

void DatasetArray::Remove(Dataset *dataset)
{
        std::vector<Dataset*>::iterator pos = find(m_datasetarray.begin(), m_datasetarray.end(), dataset);

        if (pos != m_datasetarray.end()) {
            SAFE_UNREF(dataset);
            m_datasetarray.erase(pos);
        }
}

void DatasetArray::RemoveAt(size_t index, size_t count)
{
        for (size_t n = index; n < index + count; n++) {
            SAFE_UNREF(m_datasetarray.at(n));
        }

        m_datasetarray.erase(m_datasetarray.begin() + index, m_datasetarray.begin() + index + count);
}
