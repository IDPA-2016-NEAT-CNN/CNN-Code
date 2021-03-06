#pragma once
#include "filter.hpp"

namespace Convolutional::Layer {
class Filters : public ILayer {
public:
	using ILayer::ILayer;
	Filters(std::size_t filterCount = 4): filters{ filterCount } {}

	auto ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix override;

	auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override { return filters.front().GetReceptiveField(size); }
	auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override { return filters.front().GetZeroPadding(size); }
	auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size override { return filters.front().GetStride(size); }

	auto Clone() const noexcept->std::unique_ptr<ILayer> override { return std::make_unique<Filters>(*this); }

private:
	std::vector<Filter> filters;
};

}
